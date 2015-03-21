app.controller('domainController', function ($scope, $http, $location) {

    $scope.servidor = 'http://127.0.0.1:82/cgi-bin/SpacedRepetitionSoftware.exe?';

    $scope.ROUTE_CAD_DECK = "cre/deck/";
    $scope.ROUTE_CAD_WORD = "cre/word/";


    $scope.cadastrarDeck = function (deck) {

        $http.get($scope.servidor + $scope.ROUTE_CAD_DECK + JSON.stringify(deck)).

        success(function (data, status, headers, config) {

            console.log(data);

        }).

        error(function (data, status, headers, config) {

            console(data);
            alert('erro: ' + data);

        });
    };

    $scope.cadastrarWord = function (word) {

        $http.get($scope.servidor + $scope.ROUTE_CAD_WORD + JSON.stringify(word)).

        success(function (data, status, headers, config) {

            console.log(data);

        }).

        error(function (data, status, headers, config) {

            console(data);
            alert('erro: ' + data);

        });
    };


});


