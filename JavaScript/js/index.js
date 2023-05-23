// SELECIONANDO OS OBJETOS HTML QUE SERAM USADOS
// ---- DIVS PRINCIPAIS
const makeReservations = document.getElementById("makeReservations");
const deleteReservations = document.getElementById("deleteReservations");
const listReservations = document.getElementById("listReservations");
const seekReservations = document.getElementById("seekReservations");
const editReservations = document.getElementById("editReservations");
const availableRooms = document.getElementById("availableRooms");
const numberOfGuests = document.getElementById("numberOfGuests");

// ---- OUTROS ELEMENTOS HTML
const roomList = document.getElementById("roomList");

// OBJETOS USADOS NO CODIGO

let room = {
  availablity: "",
  price: null,
  location: "",
  number: null,
};

let guest = {
  nameGuest: "",
  lengthOfStay: 0,
  docGuest: 0,
  roomGuest: 0,
  next: null,
};

// ------------------------------- COLOCAR A VERIFIAÇÃO PARA QUANDO JA TIVER RESERVAS FEITAS
let headList = null;

//FUNÇÕES SOBRE A LISTA DE HOSPEDES

function createNode() {
  return guest;
}

function createReserve() {
  const newNode = createNode();

  if (!headList) {
    //CAPUTAR OS VALORES DOS INPUTS E COLOCAR AQUI
    newNode.nameGuest = "";
    newNode.lengthOfStay = 3;
    newNode.docGuest = 12354;
    newNode.roomGuest = 4;
    headList = newNode;
  } else {
    let current = headList;
    //fazer o while de forma que insira de maneira ordenada.
  }
}

// FUNÇÕES SOBRE OS QUARTOS DO HOTEL

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

// EVENTOS DISPARADOS NO CODIGO

window.addEventListener("DOMContentLoaded", () => {
  captureRooms().then(() => {
    showAvailableRooms();
  });
});

document.addEventListener("clcik", () => {
  showAvailableRooms();
});
