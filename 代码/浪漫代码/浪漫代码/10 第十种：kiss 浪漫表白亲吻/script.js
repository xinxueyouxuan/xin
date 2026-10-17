// credit to the original svg https://www.vectorstock.com/royalty-free-vector/flat-with-shadow-icon-and-mobile-application-kiss-vector-6341903

var master = new TimelineMax();
var couple = $('#couple');
var girl = $('#girl');
var boy = $('#boy');
var heart = $('#heart');
var ground = $('#ground');
var background = $('body');
var light = $('#triangle-light');
// $('.container').append(new Array(50).join('<div class="heart"></div>'));


master
  .add(setup)
  .add(darkness, 'lightsOff+=1')
  .add(girlKiss, 'girlStuff+=1')
  .add(boyStuff, 'girlStuff+=2')
  .add(heartStuff, 'heartStuff')
  .add(lightsOn, 'heartStuff+=2');


function setup() {
  var tl = new TimelineMax();
  tl
  .set(couple, {autoAlpha: 1})
  .set(girl.find('#girl-earring'), {scaleY: '0.7'})
  .set(girl.find('#girl-leg-1'), {rotation: '+=75'})
  .set(girl.find('#girl-arm'), {transformOrigin: '100% 0%', rotation: '-=60'})
  .set(girl.find('#girl-body'), {transformOrigin: '0% 75%', rotation: '+=20'})
  .set(heart, {transformOrigin: '50% 50%', y: '+=100', scale: 0.5});
  
  return tl;
}


function darkness() {
  var tl = new TimelineMax();
  tl.to(background, 1, {backgroundColor: '#241a22'});
  return tl;
}

function girlKiss() {
  var tl = new TimelineMax();
  tl
  .to(girl.find('#girl-arm'), 1, { rotation: 0})
  .to(girl.find('#girl-body'), 0.5, {transformOrigin: '0% 75%', rotation: 0})
  .to(girl.find('#girl-eye'), 0.5, {transformOrigin: '0% 50%', scaleY: 0.1}, 1.25)
  .to(girl.find('#girl-leg-1'), 1.5, {rotation: 0, ease: Back.easeOut.config(3)}, 1.25);
  
  return tl;
}


function boyStuff() {
  var tl = new TimelineMax();
  tl
    .to(boy.find('#boy-eye'), 0.5, {transformOrigin: '0% 50%', scaleY: 0.1})
  
  return tl;
}

function heartStuff() {
  var tl = new TimelineMax();
  tl
  .to('#heart', 1, { autoAlpha: 1, y: 0, scale: 1});
  return tl;
}


function lightsOn() {
  var tl = new TimelineMax();
  tl
  .to(light, 0.25, {autoAlpha: 1}, 0)
  .to(ground, 0.25, {fill: '#F8E5C5'}, 0)
  .to(girl.find('#girl-eye'), 0.5, {scaleY: 1}, 0.5)
  .to(boy.find('#boy-eye'), 0.5, { scaleY: 1}, 1)
  .to(girl.find('#girl-leg-1'), 1, {rotation: '+=75'})
  .to(girl.find('#girl-body'), 0.5, { rotation: '+=20'})
 // .to(girl.find('#girl-face'), 0.5, { rotation: '-=20'});
  
  
  
  return tl;
  
}