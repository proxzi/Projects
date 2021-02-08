document.onreadystatechange = function () {

  if (document.readyState === 'complete') {
    'use strict';

    let placeholder = document.getElementById('placeholder');

    function updateText(packageSource, path) {

      placeholder.innerHTML = marked(packageSource);

      $('img').each(function () {
        let href = $(this).attr('src');
        $(this).attr('src', path + '/' + href);
        $(this).attr('width', '100%');
        $(this).attr('height', '100%');
      });

      placeholder.innerHTML = placeholder.innerHTML.split('[]').join('&#8195;&#8195;');

      Array.from(document.getElementsByTagName('code')).forEach((block) => {
        hljs.highlightBlock(block);
      });

      $("table").wrap(`<div class='table'></div>`);

      $('button').each(function () {
        let id = $(this).attr('id');
        $(this).replaceWith(`
          <div class="button">
            <a href = "edit-current::/${id}">
                <button>Попробовать в редакторе</button>
            </a>
            <a href = "edit-new::/${id}">
                <button>Попробовать в новом окне</button>
            </a>
          <div>`);
      });

      window.scrollTo(0, 0);
    }

    new QWebChannel(qt.webChannelTransport,
      function (channel) {

        let tutorialPackage = channel.objects.tutorialPackage;
        tutorialPackage.textChanged.connect(updateText);
      }
    );
  }
}