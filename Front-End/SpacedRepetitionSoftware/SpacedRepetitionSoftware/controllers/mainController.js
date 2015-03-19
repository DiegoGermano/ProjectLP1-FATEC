app.controller('mainController', function ($scope, $http, $location) {

    $scope.servidor = 'http://127.0.0.1:82/cgi-bin/SpacedRepetitionSoftware.exe?';

    $scope.ROUTE_CAD_DECK = "cre/deck/";
    $scope.ROUTE_CAD_WORD = "cre/word/";
    $scope.ROUTE_CAD_USER = "cre/user/";
    $scope.ROUTE_CAD_CONT = "cre/cont/";

    $scope.ROUTE_CAD_LOGI = "log/logi/";

    $scope.contacts = [];

   

    //login

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


    //Manipulations contact
    $scope.addContact = function (contact) {

        $scope.contacts.push(angular.copy(contact));

    };

    $scope.removeContact = function (contact) {

        $scope.contacts.splice($scope.contacts.indexOf(contact), 1);
    };


    //Creators
    $scope.cadastrarUser = function (user) {

        $http.get($scope.servidor + $scope.ROUTE_CAD_USER + JSON.stringify(user) +"&121dsa2d41sa2d1sa2x2x4asd2sa1xas45dx1as2").

        success(function (data, status, headers, config) {

            console.log(data);

            for (var i = 0; i < $scope.contacts.length ; i++) {

                $scope.contacts[i].usuario_id = data;

                $http.get($scope.servidor + $scope.ROUTE_CAD_CONT + JSON.stringify($scope.contacts[i])).

                    success(function (data, status, headers, config) {

                        console.log(data);

                    });

            }
            
        }).

        error(function (data, status, headers, config) {

            console(data);
            alert('erro: ' + data);

        });
    };

    $scope.cadastrarDeck = function (deck) {

        $http.get($scope.servidor+$scope.ROUTE_CAD_DECK  + JSON.stringify(deck) ).

        success(function (data, status, headers, config) {

            console.log(data);

        }).

        error(function (data, status, headers, config) {

            console(data);
            alert('erro: '+data);

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
