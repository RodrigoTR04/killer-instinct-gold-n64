#!/usr/bin/env python3
"""Generate a self-contained offline treemap from the function inventory."""
import argparse
import html
import json
from pathlib import Path
from progress import ROOT, read_inventory, report

COLORS = {'T1': '#748195', 'T2': '#e7ae50', 'T3': '#5794e2', 'T4': '#45b983', 'excluded': '#aa83d6'}
SVG_W, SVG_H = 1600, 900


def layout(items, x, y, w, h):
    if not items or w <= 0 or h <= 0:
        return []
    total = sum(item['bytes'] for item in items)
    if total <= 0:
        return []
    scale = w * h / total
    todo = sorted(({**item, 'value': item['bytes'] * scale} for item in items),
                  key=lambda item: item['value'], reverse=True)
    out = []

    def worst(row, side):
        if not row:
            return float('inf')
        total_row = sum(item['value'] for item in row)
        return max(side * side * row[0]['value'] / (total_row * total_row),
                   total_row * total_row / (side * side * row[-1]['value']))

    while todo:
        row, side = [todo.pop(0)], min(w, h)
        while todo and worst(row + [todo[0]], side) <= worst(row, side):
            row.append(todo.pop(0))
        total_row, offset = sum(item['value'] for item in row), 0
        if w >= h:
            width = total_row / h
            for item in row:
                height = item['value'] / width
                out.append({**item, 'x': x, 'y': y + offset, 'w': width, 'h': height})
                offset += height
            x, w = x + width, max(0, w - width)
        else:
            height = total_row / w
            for item in row:
                width = item['value'] / height
                out.append({**item, 'x': x + offset, 'y': y, 'w': width, 'h': height})
                offset += width
            y, h = y + height, max(0, h - height)
    return out


def write_svg(rows, path):
    parts = [f'<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 {SVG_W} {SVG_H + 30}" width="{SVG_W}" height="{SVG_H + 30}">',
             f'<rect width="{SVG_W}" height="{SVG_H + 30}" fill="#111827"/>']
    areas = [{'area': area, 'bytes': sum(r['bytes'] for r in rows if r['area'] == area)}
             for area in sorted({r['area'] for r in rows})]
    for area in layout(areas, 0, 0, SVG_W, SVG_H):
        parts.append(f'<rect x="{area["x"]:.2f}" y="{area["y"]:.2f}" width="{area["w"]:.2f}" height="{area["h"]:.2f}" fill="#1f2937"/>')
        if area['w'] > 70 and area['h'] > 22:
            parts.append(f'<text x="{area["x"] + 5:.2f}" y="{area["y"] + 16:.2f}" fill="#f3f4f6" font-size="13" font-family="system-ui,sans-serif">{html.escape(area["area"])}</text>')
        inner = layout([r for r in rows if r['area'] == area['area']],
                       area['x'] + 2, area['y'] + 20, max(0, area['w'] - 4), max(0, area['h'] - 22))
        for row in inner:
            title = html.escape(f'{row["function"]} · {row["vram"]} · {row["bytes"]} bytes · {row["tier"]}')
            parts.append(f'<rect x="{row["x"]:.2f}" y="{row["y"]:.2f}" width="{max(row["w"] - 0.6, 0.4):.2f}" height="{max(row["h"] - 0.6, 0.4):.2f}" fill="{COLORS[row["tier"]]}" stroke="#111827"><title>{title}</title></rect>')
    matched = sum(r['bytes'] for r in rows if r['tier'] == 'T4')
    total = sum(r['bytes'] for r in rows)
    t4 = sum(r['tier'] == 'T4' for r in rows)
    t3 = sum(r['tier'] == 'T3' for r in rows)
    parts.append(f'<text x="12" y="{SVG_H + 20}" fill="#d1d5db" font-size="13" font-family="system-ui,sans-serif">'
                 f'T4 byte-exact {t4} · T3 contract-valid {t3} · {matched:,}/{total:,} bytes exact '
                 f'({100 * matched / total if total else 0:.1f}%) · green=T4 blue=T3 amber=T2 gray=T1 purple=excluded</text>')
    parts.append('</svg>\n')
    path.write_text('\n'.join(parts))
    print(f'Generated {path.relative_to(ROOT) if path.is_relative_to(ROOT) else path}')


def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('--input', type=Path, default=ROOT / 'docs/functions.csv')
    p.add_argument('--output', type=Path, default=ROOT / 'docs/progress.html')
    p.add_argument('--svg', nargs='?', const=ROOT / 'docs/progress-map.svg', type=Path)
    p.add_argument('--html', action='store_true', default=True)
    p.add_argument('--no-html', dest='html', action='store_false')
    args = p.parse_args()
    rows = read_inventory(args.input)
    data = report(rows)
    summary = []
    for metric in ('M1', 'M2'):
        d = data[metric]
        percent = f'{d["percent"]:.2f}%' if d['percent'] is not None else 'n/a'
        summary.append(f'{metric}: {d["bytes"]:,} / {data["eligible_bytes"]:,} bytes ({percent})')
    payload = json.dumps(rows, separators=(',', ':')).replace('<', '\\u003c')
    page = '''<!doctype html><html lang="en"><meta charset="utf-8">
<meta name="viewport" content="width=device-width,initial-scale=1"><title>Killer Instinct Gold progress</title>
<style>
body{margin:24px;background:#111827;color:#f3f4f6;font:16px system-ui}h1{font-size:26px}
#map{width:100%;height:72vh;min-height:450px;background:#1f2937}svg{display:block;width:100%;height:100%}
.legend{display:flex;gap:18px;flex-wrap:wrap;margin:16px 0}.dot{display:inline-block;width:12px;height:12px;margin-right:5px}
text{fill:white;font:12px system-ui;pointer-events:none}rect{stroke:#111827;stroke-width:1}g:focus rect,g:hover rect{stroke:white;stroke-width:2}
#detail{min-height:3em;white-space:pre-wrap}p{color:#d1d5db}
</style><h1>Killer Instinct Gold — function progress</h1><p>SUMMARY</p>
<p>COUNTS</p><div class="legend" id="legend"></div>
<p>Areas group functions; rectangle area represents original bytes. Hover or focus a function for details.</p>
<div id="map"><svg role="img" aria-label="Function treemap sized by original bytes"></svg></div><p id="detail" aria-live="polite"></p>
<p>Scope: extracted assembly functions only; opaque compressed code is not yet inventoried.
Excluded functions remain visible and are omitted only from the eligible denominator.</p>
<script>
const rows=PAYLOAD;
const colors={T1:'#748195',T2:'#e7ae50',T3:'#5794e2',T4:'#45b983',excluded:'#aa83d6'};
const svg=document.querySelector('svg'),NS='http://www.w3.org/2000/svg';
for(const [tier,color] of Object.entries(colors)){const el=document.createElement('span'),dot=document.createElement('i');dot.className='dot';dot.style.background=color;el.append(dot,document.createTextNode(tier));document.querySelector('#legend').append(el);}
function node(tag,attrs,parent){const n=document.createElementNS(NS,tag);for(const [k,v] of Object.entries(attrs))n.setAttribute(k,v);parent.append(n);return n;}
// Squarified layout: greedily extend a row while its worst aspect ratio improves.
function layout(items,x,y,w,h){
 if(!items.length||w<=0||h<=0)return [];
 const total=items.reduce((s,i)=>s+i.bytes,0),scale=w*h/total;
 let todo=items.map(i=>({...i,value:i.bytes*scale})).sort((a,b)=>b.value-a.value),out=[];
 function worst(row,side){if(!row.length)return Infinity;const sum=row.reduce((s,i)=>s+i.value,0);return Math.max(side*side*row[0].value/(sum*sum),sum*sum/(side*side*row[row.length-1].value));}
 while(todo.length){let row=[todo.shift()],side=Math.min(w,h);while(todo.length&&worst([...row,todo[0]],side)<=worst(row,side))row.push(todo.shift());
 const sum=row.reduce((s,i)=>s+i.value,0);let offset=0;
 if(w>=h){const width=sum/h;for(const i of row){const height=i.value/width;out.push({...i,x,y:y+offset,w:width,h:height});offset+=height;}x+=width;w=Math.max(0,w-width);}
 else{const height=sum/w;for(const i of row){const width=i.value/height;out.push({...i,x:x+offset,y,w:width,h:height});offset+=width;}y+=height;h=Math.max(0,h-height);}
 }return out;
}
function draw(){svg.replaceChildren();const w=svg.clientWidth,h=svg.clientHeight;svg.setAttribute('viewBox',`0 0 ${w} ${h}`);
 const areas=[...new Set(rows.map(r=>r.area))].map(area=>({area,bytes:rows.filter(r=>r.area===area).reduce((s,r)=>s+r.bytes,0)}));
 for(const a of layout(areas,0,0,w,h)){node('rect',{x:a.x,y:a.y,width:a.w,height:a.h,fill:'#263449'},svg);const title=node('text',{x:a.x+5,y:a.y+16},svg);title.textContent=a.area;
 for(const r of layout(rows.filter(r=>r.area===a.area),a.x+2,a.y+23,Math.max(0,a.w-4),Math.max(0,a.h-25))){
 const g=node('g',{tabindex:0},svg),detail=`${r.function} · ${r.vram} · ROM ${r.rom}\n${r.bytes.toLocaleString()} bytes · ${r.tier}${r.note?' · '+r.note:''}`;
 g.setAttribute('aria-label',detail);node('rect',{x:r.x,y:r.y,width:r.w,height:r.h,fill:colors[r.tier]},g);node('title',{},g).textContent=detail;
 if(r.w>95&&r.h>20)node('text',{x:r.x+4,y:r.y+15},g).textContent=r.function.slice(0,Math.floor(r.w/7));
 for(const event of ['mouseenter','focus'])g.addEventListener(event,()=>document.querySelector('#detail').textContent=detail);
 }}
}new ResizeObserver(draw).observe(document.querySelector('#map'));
</script></html>'''
    counts = ' · '.join(f'{t}: {v["functions"]} functions / {v["bytes"]:,} bytes' for t,v in data['tiers'].items())
    page = page.replace('SUMMARY', html.escape(' · '.join(summary))).replace('COUNTS', html.escape(counts)).replace('PAYLOAD', payload)
    if args.html:
        args.output.write_text(page)
        print(f'Generated {args.output.relative_to(ROOT) if args.output.is_relative_to(ROOT) else args.output}')
    if args.svg is not None:
        write_svg(rows, args.svg)


if __name__ == '__main__':
    main()
