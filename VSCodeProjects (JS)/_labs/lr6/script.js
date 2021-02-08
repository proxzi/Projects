window.onload = function () {
	var counter = 0;
	let count = document.getElementById('Display');
	function fill() {

		document.querySelectorAll('div').forEach(element => {
			element.onclick = function () { };
			element.style.backgroundImage = 'url(without.png)';
		});


		let field = document.getElementById(Math.floor(Math.random() * 9));
		field.style.backgroundImage = 'url(with.png)';

		field.onclick = function () {
			this.onclick = function () { };
			this.style.backgroundImage = 'url(without.png)';
			count.innerHTML = ++counter;
		};
	}
	setInterval(fill, 700);
};
