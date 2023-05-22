let roomList = document.getElementById("roomList");
let roomVector = [];

function captureRooms() {
  return fetch("http://127.0.0.1:5500/JavaScript/js/quartos.json")
    .then((response) => response.json())
    .then((quartos) => {
      roomVector = quartos.dados;
      return roomVector;
    });
}

function showAvailableRooms(roomVector) {
  console.log(roomVector);
  roomVector.forEach((quarto) => {
    roomList.innerHTML += `<li> <strong>Disponibilidade:</strong> ${quarto.disponibilidade} || <strong>Preço:</strong> ${quarto.preco} || <strong>Localização:</strong> ${quarto.localizacao}</li>`;
  });
}

window.addEventListener("DOMContentLoaded", () => {
  captureRooms().then((roomVector) => {
    showAvailableRooms(roomVector);
  });
});
