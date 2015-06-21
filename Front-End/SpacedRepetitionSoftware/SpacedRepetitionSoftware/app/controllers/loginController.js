app.controller('loginController', function ($scope, $http, $location, UserService) {


    $scope.servidor = 'http://127.0.0.1:82/cgi-bin/SpacedRepetitionSoftware.exe?';

    $scope.ROUTE_CAD_LOGI = "log/logi/";

    $scope.logIn = function (user) {

        $http.get($scope.servidor + $scope.ROUTE_CAD_LOGI + JSON.stringify(user)).

        success(function (data, status, headers, config) {
            
            
            if (data.indexOf("denied") > -1) {

                $("#lb_invalidlogin").hide(50);
                $("#lb_invalidlogin").show("slow");
                $("#lb_fisttimelogin").hide();
                return;
            }

            UserService.token = data;

            console.log(data);

            $("#divLogin").hide(100);
            $location.path("/domain");
        }).

        error(function (data, status, headers, config) {

            alert('erro: ' + data);

        });
    };

    $scope.btnCancelarLogin = function () {

        $("#divLogin").hide(200);

    };

    initializeJQueryEvents();

});

