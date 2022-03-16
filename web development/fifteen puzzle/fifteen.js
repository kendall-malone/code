let ROWS= 3;
let COLUMNS= 3;
let SQUARE_SIZE=100;
let emptyrow=3;
let emptycolumn=3;

addEventListener("DOMContentLoaded", domLoaded);

function domLoaded(){
console.log("hello");
let squareArea= document.getElementById("squarearea");
for(let i=0; i<15;i++){
  var square= document.createElement("div");
  square.innerHTML=i+1;
  square.classList.add("piece");
  let row=Math.floor(i/4);
  let column=(i%4);
  square.id="square_"+row+"_"+column;
  square.style.left=column * 100 + "px";
  square.style.top=row * 100 + "px";
  squareArea.appendChild(square);
  square.style.backgroundPosition= (-column * 100)+ "px " +(-row*100)+ "px";
  square.addEventListener("mousedown", isClicked);
  square.addEventListener("mouseover", cellMouseOver);
  square.addEventListener("mouseout", cellMouseOut);
  }


}

function isClicked(){
if(isMovable(this)){
moveSquare(this);
}
}

function cellMouseOver(){
if(isMovable(this))
this.classList.add("movable");
}

function cellMouseOut(){
this.classList.remove("movable");
}

function isMovable(square){
let row= getRowCol(square.style.top);
let column= getRowCol(square.style.left);
return(row == ROWS && Math.abs(column -COLUMNS ) == 1) || (column == COLUMNS && Math.abs(row - ROWS) == 1);
}

function moveSquare(square){
square.id = "square_" + ROWS + "_" + COLUMNS;
var tempr= getRowCol(square.style.top);
var tempc= getRowCol(square.style.left);
square.style.top=ROWS*100+"px";
square.style.left=COLUMNS*100+"px";
ROWS=tempr;
COLUMNS=tempc;
//checkwin();

}

 function shuffle(){
  //alert("yes");
  for(let i=0;i<500;i++){
  let neighbors=[];
  if(ROWS<2){
  neighbors.push(document.getElementById("square_"+(ROWS+1)+"_"+COLUMNS));
  }
  if(ROWS>0){
  neighbors.push(document.getElementById("square_"+(ROWS-1)+"_"+COLUMNS));
  }
  if(COLUMNS<2){
  neighbors.push(document.getElementById("square_"+ROWS+"_"+(COLUMNS+1)));
  }
  if(COLUMNS>0){
  neighbors.push(document.getElementById("square_"+ROWS+"_"+(COLUMNS-1)));
  }
  var ranindex= parseInt(Math.random()*neighbors.length);
  moveSquare(neighbors[ranindex]);

  }
 }

function getRowCol(measure) {
        return parseInt(measure) / SQUARE_SIZE;
    }
