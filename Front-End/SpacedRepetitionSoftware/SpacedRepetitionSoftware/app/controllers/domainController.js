app.controller('domainController', function ($scope, $http, $location, UserService) {

    initializeJQueryEvents();

    $scope.current_date = new Date();

    $scope.servidor = 'http://127.0.0.1:82/cgi-bin/SpacedRepetitionSoftware.exe?';

    $scope.ROUTE_CAD_DECK = "cre/deck/";
    $scope.ROUTE_CAD_WORD = "cre/word/";
    $scope.ROUTE_REA_DECK = "rea/deck/";

    $scope.decks = null;

    $http.get($scope.servidor + $scope.ROUTE_REA_DECK).

    success(function (data, status, headers, config) {

        console.log(data);
        $scope.decks = data;

    }).

    error(function (data, status, headers, config) {

        console(data);
        alert('erro: ' + data);

    });

    $scope.AddWord = function (deck) { 
    
        $("#divNewWord").show(50);
    
    };

    $scope.Study = function (deck) {

        $("#divStudy").show(50);

    };

    $scope.History = function (deck) {

        $("#divHistory").show(50);

    };

    $scope.cadastrarDeck = function (deck) {

        deck.user_id = 75;    //get later
        deck.language_id = 1; //ger later
        deck.level = 1; //easy
        deck.activated = 1; 

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


