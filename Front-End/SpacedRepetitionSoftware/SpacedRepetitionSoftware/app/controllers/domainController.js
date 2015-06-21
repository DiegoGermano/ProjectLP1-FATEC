app.controller('domainController', function ($scope, $http, $location, UserService) {

    initializeJQueryEvents();

    $scope.current_date = new Date();

    $scope.servidor = 'http://127.0.0.1:82/cgi-bin/SpacedRepetitionSoftware.exe?';

    $scope.ROUTE_CAD_DECK = "cre/deck/";
    $scope.ROUTE_CAD_WORD = "cre/word/";
    $scope.ROUTE_CAD_STUY = "cre/stuy/";
    $scope.ROUTE_REA_DECK = "rea/deck/";
    $scope.ROUTE_REA_WORD = "rea/word/";
    $scope.ROUTE_DEL_DECK = "del/deck/";
    $scope.ROUTE_REA_HIST = "rea/hist/";

    $scope.decks = null;
    $scope.words = null;
    $scope.deckRef = null;
    $scope.forgot_the_word = null;

    $scope.LoadDecks = function () {

        $http.get($scope.servidor + $scope.ROUTE_REA_DECK + UserService.token).

        success(function (data, status, headers, config) {

            console.log(data);

            if (data != "(null)")
                $scope.decks = data;

        }).

        error(function (data, status, headers, config) {

            console(data);
            alert('erro: ' + data);

        });

    };

    $scope.AddWord = function (deck) {

        $scope.deckRef = deck;
        $("#divNewWord").show(50);
    };

    $scope.Delete = function (deck) {

        $scope.deckRef = deck;
        $("#divDelete").show(50);
    };

    $scope.cancelDelete = function () {

        $scope.deckRef = null;
        $("#divDelete").hide(50);
    };

    $scope.confirmDelete = function () {


        $http.get($scope.servidor + $scope.ROUTE_DEL_DECK + $scope.deckRef.id).

            success(function (data, status, headers, config) {

                console.log(data);
                $scope.LoadDecks();
                $("#divStudy").hide(50);
                $("#divDelete").hide(50);
                $scope.deckRef = null;
                return;
            }).

            error(function (data, status, headers, config) {

                console(data);
                alert('erro: ' + data);
            });
    };

    $scope.Study = function (deck) {

        $scope.deckRef = deck;

        $http.get($scope.servidor + $scope.ROUTE_REA_WORD + deck.id).

        success(function (data, status, headers, config) {

            $scope.words = data;
            $scope.words.current = 0;
            $scope.words.errors = 0;
            $scope.words.percentYield = 100;

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

        if ($scope.forgot_the_word == true) {
            $scope.words.errors++;
            $scope.forgot_the_word = false;
        }

        if ($scope.words.current == $scope.words.length) {

            if ($scope.words.errors > -1) {
                $scope.words.percentYield = (parseInt($scope.words.length)-parseInt($scope.words.errors));
            }

            $http.get($scope.servidor + $scope.ROUTE_CAD_STUY + "{\"user_id\":1	,\"PercentYield\":" + $scope.words.percentYield + "	,\"Deck_Id\": " + $scope.deckRef.id + " }").

            success(function (data, status, headers, config) {

                console.log(data);

                alert("Parabens vc terminuou esse deck :)");
                $scope.LoadDecks();
                $("#divStudy").hide(50);
                return;
            }).

            error(function (data, status, headers, config) {

                console(data);
                alert('erro: ' + data);
            });
        }
        else {
            $scope.study_wordfront = $scope.words[$scope.words.current].Front;
            $scope.study_wordback = $scope.words[$scope.words.current].Back;
        }
    };

    $scope.btnForgot = function () {

        $scope.forgot_the_word = true;
        $scope.showBack = true;
    };

    $scope.History = function (deck) {

        $("#divHistory").show();

        $("#divChart").html("");

        $http.get($scope.servidor + $scope.ROUTE_REA_HIST + deck.id).

       success(function (data, status, headers, config) {

           console.log(data);

           new Morris.Bar({

               element: 'divChart',

               data: data,

               xkey: 'date',
               ykeys: ['value'],
               labels: ['Acertos']
           });


       }).

       error(function (data, status, headers, config) {

           console.log(status);
           console.log(data);
           alert('erro: ' + data);

       });

       

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
        deck.language_id = 1; //get later
        deck.level = 1; //easy
        deck.activated = 1;

        $http.get($scope.servidor + $scope.ROUTE_CAD_DECK + JSON.stringify(deck)).

        success(function (data, status, headers, config) {

            $("#divNewDeck").hide(50);

            $scope.LoadDecks();

        }).

        error(function (data, status, headers, config) {

            console(data);
            alert('erro: ' + data);

        });
    };

    $scope.LoadDecks();

});



