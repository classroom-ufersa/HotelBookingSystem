// SELECIONANDO AS DIVS PRINCIPAIS DE INTERAÇÕES

const makeReservations = document.getElementById("makeReservations");
const deleteReservations = document.getElementById("deleteReservations");
const listReservations = document.getElementById("listReservations");
const seekReservations = document.getElementById("seekReservations");
const editReservations = document.getElementById("editReservations");
const availableRooms = document.getElementById("availableRooms");
const numberOfGuests = document.getElementById("numberOfGuests");

// OUTROS ELEMENTOS HTML
const roomList = document.getElementById("roomList");

// VARIAVEIS GLOBAIS
let roomVector = [];
let name = "";
let document;
let lenghtOfStay;
let numberRoom;

function captureRooms() {
  return fetch("http://127.0.0.1:5500/JavaScript/js/quartos.json")
    .then((response) => response.json())
    .then((quartos) => {
      roomVector = quartos.dados;
      return roomVector;
    });
}

function showAvailableRooms() {
  for (let i = 0; i < roomVector.length; i++) {
    roomList.innerHTML += `<li> <strong>Disponibilidade:</strong> ${roomVector[i].disponibilidade} || <strong>Preço:</strong> ${roomVector[i].preco} || <strong>Localização:</strong> ${roomVector[i].localizacao}</li>`;
  }
}

window.addEventListener("DOMContentLoaded", () => {
  captureRooms().then((roomVector) => {
    showAvailableRooms(roomVector);
  });
});

document.addEventListener("clcik", () => {
  showAvailableRooms(roomVector);
});
