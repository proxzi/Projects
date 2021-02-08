'use strict';

var documentationPackage;

var search = function (cppClassName, cppFunctionName, hostUrl) {

  let searchValueLine = cppFunctionName === "" ? cppClassName : cppFunctionName;
  let searchResLine = cppFunctionName === "" ? cppClassName : cppClassName + "::" + cppFunctionName;
  searchBox.DOMSearchField().value = searchValueLine;
  searchBox.Search();
  searchBox.CloseResultsWindow();

  document.getElementById("MSearchResults").onload = () => {
    let searchRes = document.getElementById("MSearchResults").contentWindow.document.documentElement.innerHTML;
    let regHead = 'href\\=\\"\\.\\.\\/([^\\s]+)\\" [^\\s]+';
    let regTail = (cppFunctionName === "" ? '\\<' : '[^\\)]+\\)\\<');
    let matchRes = searchRes.match(new RegExp(regHead + searchResLine + regTail, 'i'));
  
    if (matchRes != null && matchRes.length >= 2) {
      let finalUrl = hostUrl + "/" + matchRes[1];
      document.location.href = finalUrl;
      documentationPackage.slotSearchIsSuccess(true);
      documentationPackage.slotUpdateCurrentUrl(finalUrl);
    }
  };
  //setTimeout(() => {
  //  let searchRes = document.getElementById("MSearchResults").contentWindow.document.documentElement.innerHTML;
  //  let regHead = 'href\\=\\"\\.\\.\\/([^\\s]+)\\" [^\\s]+';
  //  let regTail = (cppFunctionName === "" ? '\\<' : '[^\\)]+\\)\\<');
  //  let matchRes = searchRes.match(new RegExp(regHead + searchResLine + regTail, 'i'));
  //
  //  if (matchRes != null && matchRes.length >= 2) {
  //    let finalUrl = hostUrl + "/" + matchRes[1];
  //    document.location.href = finalUrl;
  //    documentationPackage.slotUpdateCurrentUrl(finalUrl);
  //  }
  //}, 500);
}

new QWebChannel(qt.webChannelTransport,
  function (channel) {
    documentationPackage = channel.objects.documentationPackage;
    documentationPackage.signalSearchRequest.connect(search);
  }
);