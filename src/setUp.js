function opn(){
setTimeout(function(){
document.getElementById('shut').innerHTML=2;
document.getElementById("circle").width=window.innerWidth;
document.getElementById("circle").height=window.innerHeight;
let $hg=window.innerHeight+"px";
// let $md=Math.round(parseInt(window.innerWidth,10)*0.5)-(window.innerHeight*0.5);
// let $hmd=Math.round(parseInt(window.innerHeight,10)*0.5)-(window.innerHeight*0.5);
// document.getElementById("ihig").innerHTML=window.innerHeight;
// document.getElementById("pmhig").innerHTML=window.innerHeight;
// document.getElementById("iwid").innerHTML=window.innerHeight;
// document.getElementById("canvas").style.top=0;
document.getElementById("wrap").style.lineheight=$hg;
document.getElementById("di").click();
},500);
setTimeout(function(){
document.getElementById("btn2").click();
},500);
};
