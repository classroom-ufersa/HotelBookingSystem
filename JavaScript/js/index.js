// ---- DIVS PRINCIPAIS
const makeReservations = document.getElementById("makeReservations");
const deleteReservations = document.getElementById("deleteReservations");
const listReservations = document.getElementById("listReservations");
const seekReservations = document.getElementById("seekReservations");
const editReservations = document.getElementById("editReservations");
const allRooms = document.getElementById("allRooms");
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
const btnStartRegisterstar = document.getElementById("startRegisterstar");

// INPUTS OF CODE

const inputNameResponse = document.getElementById("nameResponse");
const inputDuration = document.getElementById("lenghtOfStay");
const inputResbosibleDoc = document.getElementById("resbosibleDoc");
const inputCheckRoom = document.getElementById("inputCheckRoom");

// FUNÇÕES ASSINCRONAS DO PROGRAMA
function captureRooms() {
  return fetch("http://127.0.0.1:5500/JavaScript/js/quartos.json")
    .then((response) => response.json())
    .then((quartos) => {
      roomVector = quartos.dados;
      return roomVector;
    });
}

// ----------------TA DANDO B.O.
function writeToFile() {
  const jsonData = JSON.stringify(roomVector);

  fetch("http://127.0.0.1:5500/JavaScript/js/quartos.json", {
    method: "POST",
    headers: {
      "Content-Type": "application/json",
    },
    body: jsonData,
  })
    .then((response) => {
      if (!response.ok) {
        throw new Error("Erro na solicitação POST");
      }
      // A solicitação POST foi bem-sucedida
      // Faça qualquer ação necessária após a atualização do arquivo JSON
    })
    .catch((error) => {
      console.error("Erro na solicitação POST:", error);
      // Lide com o erro adequadamente
    });
}

// OBJETOS E VARIAVEIS GLOBAIS

let room = {
  availablity: "",
  price: null,
  location: "",
  number: null,
};

let headList = null;

let inputNumberRoom = null;

// FUNÇÕES SOBRE A INTERFACE DO PROJETO

function hideDivs() {
  makeReservations.style.display = "none";
  deleteReservations.style.display = "none";
  listReservations.style.display = "none";
  seekReservations.style.display = "none";
  editReservations.style.display = "none";
  allRooms.style.display = "none";
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
    numberRoom: 0,
    next: null,
  };
}

// falta: colocar o numero do quarto, porem para fazer isso deve-se fazer uma função que verifica se o quarto esta ocupado opu não
function createReserve() {
  const newNode = createNode();

  newNode.nameGuest = inputNameResponse.value;
  newNode.lengthOfStay = parseInt(inputDuration.value);
  newNode.docGuest = parseInt(inputResbosibleDoc.value);
  newNode.numberRoom = inputNumberRoom;

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

  inputNameResponse.value = "";
  inputDuration.value = "";
  inputResbosibleDoc.value = "";
  console.log(headList);
}

function showAvailableRooms() {
  roomList[1].innerHTML = ``;
  for (let i = 0; i < roomVector.length; i++) {
    if (roomVector[i].disponibilidade == "DISPONIVEL") {
      roomList[1].innerHTML += `<li> <strong>Disponibilidade:</strong> <span class="greenText">${roomVector[i].disponibilidade}</span> || <strong>Preço:</strong> ${roomVector[i].preco} || <strong>Localização:</strong> ${roomVector[i].localizacao} || <strong>Numero:</strong> ${roomVector[i].numero}</li>`;
    }
  }
}

function showAllRooms() {
  roomList[0].innerHTML = ``;
  for (let i = 0; i < roomVector.length; i++) {
    if (roomVector[i].disponibilidade == "DISPONIVEL") {
      roomList[0].innerHTML += `<li> <strong>Disponibilidade:</strong> <span class="greenText">${roomVector[i].disponibilidade}</span> || <strong>Preço:</strong> ${roomVector[i].preco} || <strong>Localização:</strong> ${roomVector[i].localizacao} || <strong>Numero:</strong> ${roomVector[i].numero}</li>`;
    } else {
      roomList[0].innerHTML += `<li> <strong>Disponibilidade:</strong> <span class="redText">${roomVector[i].disponibilidade}</span> || <strong>Preço:</strong> ${roomVector[i].preco} || <strong>Localização:</strong> ${roomVector[i].localizacao} || <strong>Numero:</strong> ${roomVector[i].numero}</li>`;
    }
  }
}

function verificationRoom() {
  inputNumberRoom = parseInt(inputCheckRoom.value) - 1;
  inputCheckRoom.value = "";
  if (inputNumberRoom <= 19 && inputNumberRoom >= 0) {
    if (roomVector[inputNumberRoom].disponibilidade == "OCUPADO") {
      alert("Perdão, mas este quarto ja esta ocupado!!");
      return;
    }
    hideDivs();
    roomVector[inputNumberRoom].disponibilidade = "OCUPADO";
    makeReservations.style.display = "block";
    return;
  }
  alert("Esse quarto não existe neste hotel!!");
}

function listReservation() {
  let current = headList;
  while (current) {
    console.log(current.nameGuest);
    current = current.next;
  }
}

// EVENTOS DISPARADOS NO CODIGO

window.addEventListener("DOMContentLoaded", () => {
  captureRooms();
});

realizarReserva.addEventListener("click", () => {
  hideDivs();
  checkRoom.style.display = "block";
  showAvailableRooms();
});
excluirReserva.addEventListener("click", () => {
  hideDivs();
  deleteReservations.style.display = "block";
});
listarReservas.addEventListener("click", () => {
  hideDivs();
  listReservations.style.display = "block";
  listReservation();
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
  allRooms.style.display = "block";
  showAllRooms();
});
quantitativoHospedes.addEventListener("click", () => {
  hideDivs();
  numberOfGuests.style.display = "block";
});

btnMakeReservation.addEventListener("click", (event) => {
  event.preventDefault();
  createReserve();
});

btnStartRegisterstar.addEventListener("click", () => {
  verificationRoom();
});
