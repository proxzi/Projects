class Thing {

	constructor(article, price, quantity) {

		this._article = article;
		this._price = price;
		this._quantity = quantity;
	}

	get article() {
		return this._article;
	}

	get price() {
		return this._price;
	}

	get quantity() {
		return this._quantity;
	}
}

class Egg extends Thing {

	constructor(article, price, quantity, category) {

		super(article, price, quantity);
		this._category = category;
	}

	get category() {
		return this._category;
	}
}

class Milk extends Thing {

	constructor(article, price, quantity, fatness) {

		super(article, price, quantity);
		this._fatness = fatness;
	}

	get fatness() {
		return this._fatness;
	}
}

class Apple extends Thing {
	constructor(article, price, quantity, color) {

		super(article, price, quantity);
		this._color = color;
	}

	get color() {
		return this._color;
	}
}

class Book extends Thing {
	constructor(article, price, quantity, title, author) {

		super(article, price, quantity);
		this._title = title;
		this._author = author;
	}

	get title() {
		return this._title;
	}

	get author() {
		return this._author;
	}
}

class Basket {
	constructor() {

		this._data = [];
	}

	set put(obj) {

		if (obj instanceof Egg) {

			this._data.push({
				'Тип': 'Яйца',
				'Артикул': obj.article,
				'Цена': obj.price,
				'Количество': obj.quantity,
				'Категория': obj.category
			});

		} else if (obj instanceof Milk) {

			this._data.push({
				'Тип': 'Молоко',
				'Артикул': obj.article,
				'Цена': obj.price,
				'Количество': obj.quantity,
				'Жирность': obj.fatness + '%'
			});

		} else if (obj instanceof Apple) {

			this._data.push({
				'Тип': 'Яблоко',
				'Артикул': obj.article,
				'Цена': obj.price,
				'Количество': obj.quantity,
				'Цвет': obj.color
			});

		} else if (obj instanceof Book) {

			this._data.push({
				'Тип': 'Книга',
				'Артикул': obj.article,
				'Цена': obj.price,
				'Количество': obj.quantity,
				'Название, автор': `${obj.title}, ${obj.author}`
			});

		}
	}

	showObjects() {
		$('#basketTable').empty();

		let i = 0;
		this._data.forEach(element => {

			let data = [];
			for (let el in element) {
				data.push(`${el} : ${element[el]}  `);
			}

			$('#basketTable').append(`
                <div class="row">
                    <div class="col">
                        ${data}
                    </div>
                    <div class="col-md-2">
                        <button type="button" 
                            class="btn btn-danger" onclick="deleteThing(${i++})">Удалить</button>
                    </div>
                </div>`);
		});
	}

	deleteObject(num) {
		this._data.splice(num, 1);
	}
}

function deleteThing(num) {
	basket.deleteObject(num);
	basket.showObjects();
}

var basket = new Basket();

window.onload = () => {

	basket.put = new Apple('A2', 102, 10, 'black');
	basket.put = new Egg('E1', 100, 10, 1);
	basket.put = new Book('B1', 1111, 1, 'Идиот', 'Достоевский');
	basket.put = new Milk('M1', 20, 1, '1,5');

	basket.showObjects();
};

async function onPutApple() {
	basket.put = new Apple($('#article').val(), $('#price').val(), $('#quantity').val(), $('#Proprs').val());
	let vv = await findPlayerByName('Яблоко',  $('#price').val());
	if(vv.id == -1){
		await createNewPlayer('Яблоко', $('#article').val(), $('#price').val(), $('#quantity').val(), $('#Proprs').val());
	}

	basket.showObjects();

	getAllPlayers();
}
function onPutMilk() {
	basket.put = new Milk($('#article').val(), $('#price').val(), $('#quantity').val(), $('#Proprs').val());
	basket.showObjects();
}
function onPutEgg() {
	basket.put = new Egg($('#article').val(), $('#price').val(), $('#quantity').val(), $('#Proprs').val());
	basket.showObjects();
}
function onPutBook() {
	basket.put = new Book($('#article').val(), $('#price').val(), $('#quantity').val(), $('#Proprs').val());
	basket.showObjects();
}











///



function buildTable(data) {///ЭТО НАДО ДЛЯ ВИЗУАЛКИ
	$('#playersTable').empty();
	for (let i = 0; i < data.length; i++) {
		$('#playersTable').append(
			`
				<div class="row">
					<div>
						ID: ${data[i].id}, 
						Имя: ${data[i].type}, 
						Очки: ${data[i].article},
						ID: ${data[i].price}, 
						Имя: ${data[i].quantity}, 
						Очки: ${data[i].opinion}
					</div>
				</div>
			`
		);
	}
}

let isExistPlayer = data => data.id === -1 ? true : false;

async function ajaxRequest() {

	let data = await findPlayerByName();

	if (isExistPlayer(data)) {

		await createNewPlayer();
	} else {

		await updatePlayerScore(data.id);
	}
	getAllPlayers();
}

async function getAllPlayers() {

	let res = await fetch('http://localhost:3000/players',
		{
			method: 'GET'
		});
	let data = await res.json();
	buildTable(data);
}

async function createNewPlayer(a,b,c,d,e) {

	let res = await fetch('http://localhost:3000/players',
		{
			method: 'POST',
			headers: {
				'Accept': 'application/json',
				'Content-Type': 'application/json'
			},
			body: JSON.stringify({
				type: a,
				article: b,
				price: c,
				quantity: d,		
				opinion: e			
			})
		});
	const data = await res.json();
	console.log(data);
}

async function findPlayerByName(r,a) {
	let res = await fetch(`http://localhost:3000/players/${r}/${a}`,
		{
			method: 'GET',
			headers: {
				'Accept': 'application/json',
				'Content-Type': 'application/json'
			}
		});
	let data = await res.json();
	console.log(data);
	return data;
}

async function updatePlayerScore(id) {
	let res = await fetch(`http://localhost:3000/players/${id}`,
		{
			method: 'PUT',
			headers: {
				'Accept': 'application/json',
				'Content-Type': 'application/json'
			},
			body: JSON.stringify({
				score: score
			})
		});
	console.log(await res);
}