app.controller('mainController', function ($scope, $http, $location) {

    // why I need that?
    var app = angular.module('app', []);

    $scope.servidor = 'http://127.0.0.1:82/cgi-bin/SpacedRepetitionSoftware.exe?%22{json:%20menino}%22';

    $scope.cadastrarDeck = function (deck) {

        $http.get($scope.servidor).
        success(function (data, status, headers, config) {

            alert(data);
            
        }).
        error(function (data, status, headers, config) {
            alert('erro: '+data);

        });



        //var xmlhttp;
        //if (window.XMLHttpRequest) {// code for IE7+, Firefox, Chrome, Opera, Safari
        //    xmlhttp = new XMLHttpRequest();
        //}
        //else {// code for IE6, IE5
        //    xmlhttp = new ActiveXObject("Microsoft.XMLHTTP");
        //}
        //xmlhttp.onreadystatechange = function () {
        //    if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {
        //        document.getElementById("myDiv").innerHTML = xmlhttp.responseText;
        //    }
        //}
        //xmlhttp.open("GET", $scope.servidor, true);
        //xmlhttp.send();

    };
});

