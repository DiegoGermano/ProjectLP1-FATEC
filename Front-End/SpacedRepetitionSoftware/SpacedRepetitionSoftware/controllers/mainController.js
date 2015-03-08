app.controller('mainController', function ($scope, $http, $location) {

    // why I need that?
    var app = angular.module('app', []);

    $scope.servidor = 'http://127.0.0.1:82/cgi-bin/SpacedRepetitionSoftware.exe?';

    $scope.cadastrarDeck = function (deck) {

        $http.get($scope.servidor + JSON.stringify(deck) ).

        success(function (data, status, headers, config) {

            alert(data);
            
        }).

        error(function (data, status, headers, config) {
            alert('erro: '+data);

        });
    };
});

