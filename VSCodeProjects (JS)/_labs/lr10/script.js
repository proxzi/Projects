$(function () {

	$(window).scroll(function () {
		if ($(this).scrollTop() > 1000) {
			$('div').fadeIn();
		} else {
			$('div').fadeOut();
		}
	});

	$('div').click(function () {
		$("body,html").animate({
			scrollTop: 0
		}, 800);
		return false;
	});
});