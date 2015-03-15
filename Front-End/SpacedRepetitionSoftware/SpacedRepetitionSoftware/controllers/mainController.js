app.controller('mainController', function ($scope, $http, $location) {

    $scope.servidor = 'http://127.0.0.1:82/cgi-bin/SpacedRepetitionSoftware.exe?cre/deck/';

    $scope.cadastrarDeck = function (deck) {

        $http.get($scope.servidor + JSON.stringify(deck) ).

        success(function (data, status, headers, config) {

            console.log(data);

        }).

        error(function (data, status, headers, config) {

            console(data);
            alert('erro: '+data);

        });
    };
});



