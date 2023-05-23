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

// ---- BUTTONS
const btnMakeReservation = document.getElementById("sendResevation");

// INPUTS OF CODE

const nameResponse = document.getElementById("nameResponse");
const duration = document.getElementById("lenghtOfStay");
const resbosibleDoc = document.getElementById("resbosibleDoc");

// OBJETOS USADOS NO CODIGO

let room = {
  availablity: "",
  price: null,
  location: "",
  number: null,
};

// ------------------------------- COLOCAR A VERIFIcAÇÃO PARA QUANDO JA TIVER RESERVAS FEITAS
let headList = null;

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

  newNode.nameGuest = nameResponse.value;
  newNode.lengthOfStay = parseInt(duration.value);
  newNode.docGuest = parseInt(resbosibleDoc.value);

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

// FUNÇÕES SOBRE OS QUARTOS DO HOTEL
//transformar essa função assicrona em uma fução sincrona
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

btnMakeReservation.addEventListener("click", (event) => {
  event.preventDefault();
  createReserve();
});
