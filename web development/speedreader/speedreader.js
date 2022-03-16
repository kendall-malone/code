window.onload = function(){
  document.getElementById("start").addEventListener("click", startFunction);
  document.getElementById("stop").addEventListener("click", stopFunction);
  document.getElementById("stop").disabled = true;

  document.getElementById("speed").onchange = function(){
    if(document.getElementById("stop").disabled == false){
    clearInterval(interval);
    startFunction();}
  }
};

var counter = 0;
var interval;

function doublePunctuation(text){
  var newArray = [];
  for(i=0; i<text.length; i++){
    var word = text[i];
    var wordLength = word.length;
    var lastChar = word.charAt(wordLength-1);
    if(lastChar=="." || lastChar=="!"|| lastChar==","|| lastChar=="?"|| lastChar==";"|| lastChar==":"){
    var sliced = word.slice(0,-1);
    newArray.push(sliced);
    newArray.push(sliced);
    }
    else{newArray.push(word);}
  }
  return newArray;
}


function startFunction() {
  document.getElementById("stop").disabled = false;
  document.getElementById("start").disabled = true;
  document.getElementById("textinput").disabled = true;
  var wpm = document.getElementById("speed").value;
  var size = getRadioValue();
  document.getElementById("blank").style.fontSize = size;
  var text = document.getElementById("textinput").value;
  var split = text.split(/[ \t\n]+/);
  var result = doublePunctuation(split);

  interval = setInterval(
    function() {
      var displayWord = document.getElementById("blank");
      displayWord.innerHTML = result[counter];

      counter++;
      if (getRadioValue() != size) {
        size = getRadioValue();
        document.getElementById("blank").style.fontSize = size;
      }

      if(counter==result.length){
        stopFunction();
      }
    }, wpm);

    if(counter==result.length){
      stopFunction();
    }
}

function getRadioValue() {
  var radios = document.getElementsByName('size');
  for (var i = 0, length = radios.length; i < length; i++) {
    if (radios[i].checked) {
      return radios[i].value;
      break;
    }
  }
}

function stopFunction() {
  clearInterval(interval);
  document.getElementById("blank").innerHTML = " ";
  document.getElementById("start").disabled = false;
  document.getElementById("textinput").disabled = false;
  document.getElementById("stop").disabled = true;
}
