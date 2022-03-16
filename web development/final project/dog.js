/*** Calls the dog api to randomly get a set number of images*/
function getDogImage(inputValue) {
  let requiredUrl = `https://dog.ceo/api/breeds/image/random/${inputValue}`;

  fetch(requiredUrl)
    .then(response => response.json())
    .then(responseJson => displayResults(responseJson))
    .catch(error => alert('Something went wrong. Try again later.'));
}

/*** Displays the image within the div*/
function displayResults(responseJson) {
  console.log(responseJson);
  let arrayOfImg = responseJson.message;
  let display = getImages(arrayOfImg);
  //replace the existing image with the new one
  $('.results-img').html(display);
}

/**Prepares a string of <img> elements and returns the same*/
function getImages(arrayOfImg){
    let valueToReturn = '';
    for (let i = 0; i < arrayOfImg.length; i++){
      valueToReturn += `<img src="${arrayOfImg[i]}" class="results-img">`;
    }
    return valueToReturn;
}

function watchForm() {
  $('form').submit(event => {
    event.preventDefault();
    let inputValue = $('.quantity').val();
    getDogImage(inputValue);
  });
}

$(function() {
  console.log('App loaded! Waiting for submit!');
  watchForm();
});
