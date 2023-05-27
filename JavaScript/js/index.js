// ---- DIVS PRINCIPAIS
const makeReservations = document.getElementById("makeReservations");
const deleteReservations = document.getElementById("deleteReservations");
const listReservations = document.getElementById("listReservations");
const seekReservations = document.getElementById("seekReservations");
const editReservations = document.getElementById("editReservations");
const availableRooms = document.getElementById("availableRooms");
const numberOfGuests = document.getElementById("numberOfGuests");
const checkRoom = document.getElementById("checkRoom");

// ---- OPÇÕES DO MENU
const realizarReserva = document.getElementById("realizarReserva");
const excluirReserva = document.getElementById("excluirReserva");
const listarReservas = document.getElementById("listarReservas");
const buscarReserva = document.getElementById("buscarReserva");
const editarReserva = document.getElementById("editarReserva");
const mostrarQuartos = document.getElementById("mostrarQuartos");
const quantitativoHospedes = document.getElementById("quantitativoHospedes");

// ---- OUTROS ELEMENTOS HTML
const roomList = document.getElementsByClassName("roomList");

// ---- BUTTONS
const btnMakeReservation = document.getElementById("sendResevation");

// INPUTS OF CODE

const inputNameResponse = document.getElementById("nameResponse");
const inputDuration = document.getElementById("lenghtOfStay");
const inputResbosibleDoc = document.getElementById("resbosibleDoc");
const inputCheckRoom = document.getElementById("checkRoom");

// OBJETOS E VARIAVEIS GLOBAIS

let room = {
  availablity: "",
  price: null,
  location: "",
  number: null,
};

let headList = null;

// FUNÇÕES SOBRE A INTERFACE DO PROJETO

function hideDivs() {
  makeReservations.style.display = "none";
  deleteReservations.style.display = "none";
  listReservations.style.display = "none";
  seekReservations.style.display = "none";
  editReservations.style.display = "none";
  availableRooms.style.display = "none";
  numberOfGuests.style.display = "none";
  checkRoom.style.display = "none";
}

//FUNÇÕES SOBRE A LISTA DE HOSPEDES

function createNode() {
  return {
    nameGuest: "",
    lengthOfStay: 0,
    docGuest: 0,
    roomGuest: 0,
    next: null,
  };
}

// falta: colocar o numero do quarto, porem para fazer isso deve-se fazer uma função que verifica se o quarto esta ocupado opu não
function createReserve() {
  const newNode = createNode();

  newNode.nameGuest = inputNameResponse.value;
  newNode.lengthOfStay = parseInt(inputDuration.value);
  newNode.docGuest = parseInt(inputResbosibleDoc.value);

  if (!headList || newNode.nameGuest.localeCompare(headList.nameGuest) < 0) {
    newNode.next = headList;
    headList = newNode;
  } else {
    let current = headList;
    while (
      current.next &&
      newNode.nameGuest.localeCompare(current.next.nameGuest) > 0
    ) {
      current = current.next;
    }

    newNode.next = current.next;
    current.next = newNode;
  }

  console.log(headList);
}

// FUNÇÕES SOBRE OS QUARTOS DO HOTEL - transformar essa função assicrona em uma fução sincrona
function captureRooms() {
  return fetch("http://127.0.0.1:5500/JavaScript/js/quartos.json")
    .then((response) => response.json())
    .then((quartos) => {
      roomVector = quartos.dados;
      return roomVector;
    });
}

function showAvailableRooms() {
  roomList[0].innerHTML = ``;
  roomList[1].innerHTML = ``;
  for (let i = 0; i < roomVector.length; i++) {
    if (roomVector[i].disponibilidade == "DISPONIVEL") {
      roomList[0].innerHTML += `<li> <strong>Disponibilidade:</strong> ${roomVector[i].disponibilidade} || <strong>Preço:</strong> ${roomVector[i].preco} || <strong>Localização:</strong> ${roomVector[i].localizacao}</li>`;
      roomList[1].innerHTML += `<li> <strong>Disponibilidade:</strong> ${roomVector[i].disponibilidade} || <strong>Preço:</strong> ${roomVector[i].preco} || <strong>Localização:</strong> ${roomVector[i].localizacao}</li>`;
    }
  }
}

function verificationRoom() {
  checkRoom.style.display = "block";
  showAvailableRooms();
}

// EVENTOS DISPARADOS NO CODIGO

window.addEventListener("DOMContentLoaded", () => {
  captureRooms();
});

realizarReserva.addEventListener("click", () => {
  hideDivs();
  verificationRoom();
});
excluirReserva.addEventListener("click", () => {
  hideDivs();
  deleteReservations.style.display = "block";
});
listarReservas.addEventListener("click", () => {
  hideDivs();
  listReservations.style.display = "block";
});
buscarReserva.addEventListener("click", () => {
  hideDivs();
  seekReservations.style.display = "block";
});
editarReserva.addEventListener("click", () => {
  hideDivs();
  editReservations.style.display = "block";
});
mostrarQuartos.addEventListener("click", () => {
  hideDivs();
  availableRooms.style.display = "block";
  showAvailableRooms();
});
quantitativoHospedes.addEventListener("click", () => {
  hideDivs();
  numberOfGuests.style.display = "block";
});

btnMakeReservation.addEventListener("click", (event) => {
  event.preventDefault();
  createReserve();
});
