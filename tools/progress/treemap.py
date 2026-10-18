#!/usr/bin/env python3
"""Generate a self-contained offline treemap from the function inventory."""
import argparse
import html
import json
from pathlib import Path
from progress import ROOT, read_inventory, report


def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('--input', type=Path, default=ROOT / 'docs/functions.csv')
    p.add_argument('--output', type=Path, default=ROOT / 'docs/progress.html')
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
    args.output.write_text(page)
    print(f'Generated {args.output.relative_to(ROOT) if args.output.is_relative_to(ROOT) else args.output}')


if __name__ == '__main__':
    main()
