app.controller('domainController', function ($scope, $http, $location, UserService) {

    initializeJQueryEvents();

    $scope.current_date = new Date();

    $scope.servidor = 'http://127.0.0.1:82/cgi-bin/SpacedRepetitionSoftware.exe?';

    $scope.ROUTE_CAD_DECK = "cre/deck/";
    $scope.ROUTE_CAD_WORD = "cre/word/";
    $scope.ROUTE_REA_DECK = "rea/deck/";
    $scope.ROUTE_REA_WORD = "rea/word/";

    $scope.decks = null;
    $scope.words = null;
    $scope.deckRef = null;

    $http.get($scope.servidor + $scope.ROUTE_REA_DECK).

    success(function (data, status, headers, config) {

        $scope.decks = data;

    }).

    error(function (data, status, headers, config) {

        console(data);
        alert('erro: ' + data);

    });

    $scope.AddWord = function (deck) {

        $scope.deckRef = deck;
        $("#divNewWord").show(50);
    };

    $scope.Study = function (deck) {

        $scope.deckRef = deck;

        $http.get($scope.servidor + $scope.ROUTE_REA_WORD + deck.id).

        success(function (data, status, headers, config) {

            $scope.words = data;
            $scope.words.current = 0;

            $scope.study_wordfront = $scope.words[$scope.words.current].Front;
            $scope.study_wordback = $scope.words[$scope.words.current].Back;

           
            
        }).

        error(function (data, status, headers, config) {

            console(data);
            alert('erro: ' + data);

        });

        $("#divStudy").show(50);
    };

    $scope.Next = function (deck) {

        $scope.showBack = false;
        $scope.words.current++;

        if ($scope.words.current == $scope.words.length)
        {
            alert("Parabens vc terminuou esse deck :)");
            $("#divStudy").hide(50);
            return;
        }

        $scope.study_wordfront = $scope.words[$scope.words.current].Front;
        $scope.study_wordback = $scope.words[$scope.words.current].Back;

    };


    $scope.History = function (deck) {

        $("#divHistory").show(50);

    };

    $scope.cadastrarWord = function (word) {

        word.deck_id = $scope.deckRef.id;

        $http.get($scope.servidor + $scope.ROUTE_CAD_WORD + JSON.stringify(word)).

         success(function (data, status, headers, config) {

             $scope.deckRef.amountWord++;

             word.front = "";
             word.back = "";

         }).

         error(function (data, status, headers, config) {

             console(data);
             alert('erro: ' + data);

         });

    }

    $scope.cadastrarDeck = function (deck) {

        deck.user_id = 75;    //get later
        deck.language_id = 1; //ger later
        deck.level = 1; //easy
        deck.activated = 1;

        $http.get($scope.servidor + $scope.ROUTE_CAD_DECK + JSON.stringify(deck)).

        success(function (data, status, headers, config) {

            deck.id = 99999999999;
            $scope.decks.push(angular.copy(deck));
            //$("#divNewDeck").hide(50);

        }).

        error(function (data, status, headers, config) {

            console(data);
            alert('erro: ' + data);

        });
    };

});


