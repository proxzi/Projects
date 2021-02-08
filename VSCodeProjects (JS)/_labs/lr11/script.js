$(() => {
	let N, M;
	let emptyField = {};
	let fields = document.querySelectorAll('td');
	let i = 1,
		j = 1;

	let findEmptyField = field => {
		if (field.className === 'empty') {
			N = field.getAttribute('n');
			M = field.getAttribute('m');
			emptyField = field;
		}
	};

	let switchFields = (a, b) => {
		var temp = a.innerHTML;
		a.innerHTML = b.innerHTML;
		b.innerHTML = temp;

		temp = a.className;
		a.className = b.className;
		b.className = temp;

		N = a.getAttribute('n');
		M = a.getAttribute('m');
	};

	fields.forEach(field => {
		field.id = '' + i + j;
		field.setAttribute('n', i);
		field.setAttribute('m', j++);
		if (j > 4) {
			j = 1;
			i++;
		}
		findEmptyField(field);
	});	

	fields.forEach(field => {
		field.onclick = () => {
			if ((Math.abs(N - field.getAttribute('n')) === 1 && M === field.getAttribute('m')) || (N === field.getAttribute('n') && Math.abs(M - field.getAttribute('m')) === 1))
				switchFields(field, emptyField);
			findEmptyField(field);
		};
	});
});