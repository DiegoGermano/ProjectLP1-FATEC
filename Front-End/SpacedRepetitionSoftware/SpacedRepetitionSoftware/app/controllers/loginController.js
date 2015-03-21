app.controller('loginController', function ($scope, $http, $location) {

    $scope.servidor = 'http://127.0.0.1:82/cgi-bin/SpacedRepetitionSoftware.exe?';

    $scope.ROUTE_CAD_LOGI = "log/logi/";

    $scope.logIn = function (user) {

        $http.get($scope.servidor + $scope.ROUTE_CAD_LOGI + JSON.stringify(user)).

        success(function (data, status, headers, config) {

            console.log(data);

        }).

        error(function (data, status, headers, config) {

            console(data);
            alert('erro: ' + data);

        });
    };

});

