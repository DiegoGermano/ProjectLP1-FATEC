app.controller('userController', function ($scope, $http, $location, UserService) {


    initializeJQueryEvents();

    $scope.servidor = 'http://127.0.0.1:82/cgi-bin/SpacedRepetitionSoftware.exe?';

    $scope.ROUTE_CAD_USER = "cre/user/";
    $scope.ROUTE_CAD_CONT = "cre/cont/";

    $scope.contacts = [];

    $scope.cadastrarUser = function (user) {

        $http.get($scope.servidor + $scope.ROUTE_CAD_USER + JSON.stringify(user)).

        success(function (data, status, headers, config) {

            if (data == "DATABASEERROR")
            {
                alert("Email indisponivel");
                return;
            }

            for (var i = 0; i < $scope.contacts.length ; i++) {

                $scope.contacts[i].user_id = data;

                $http.get($scope.servidor + $scope.ROUTE_CAD_CONT + JSON.stringify($scope.contacts[i])).

                    success(function (data, status, headers, config) {

                        console.log(data);

                    });

            }

            alert("Usuário cadastrado com sucesso");

            $location.path("/login");

        }).

        error(function (data, status, headers, config) {

            console(data);
            alert('erro: ' + data);

        });
    };
  
    //Manipulations contact
    $scope.addContact = function (contact) {

        $scope.contacts.push(angular.copy(contact));

    };

    $scope.removeContact = function (contact) {

        $scope.contacts.splice($scope.contacts.indexOf(contact), 1);
    };
});
