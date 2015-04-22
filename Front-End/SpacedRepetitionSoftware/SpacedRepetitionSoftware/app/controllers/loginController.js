app.controller('loginController', function ($scope, $http, $location, UserService) {

    initializeJQueryEvents();

    $scope.servidor = 'http://127.0.0.1:82/cgi-bin/SpacedRepetitionSoftware.exe?';

    $scope.ROUTE_CAD_LOGI = "log/logi/";

    $scope.logIn = function (user) {

        $http.get($scope.servidor + $scope.ROUTE_CAD_LOGI + JSON.stringify(user)).

        success(function (data, status, headers, config) {
            
            
            if (data.indexOf("denied") > -1) {
                alert("Usuario ou senha invalido");
                return;
            }

            UserService.token = data;

            $location.path("/domain");


        }).

        error(function (data, status, headers, config) {

            alert('erro: ' + data);

        });
    };


});

