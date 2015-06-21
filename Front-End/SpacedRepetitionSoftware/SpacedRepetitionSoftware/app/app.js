var app = angular.module('app', ['ngRoute']);

app.config(function ($routeProvider, $locationProvider) {

    // remove o # da url
    $locationProvider.html5Mode(true);

    $routeProvider

    .when('/', {
        templateUrl: 'app/views/home.html',
        controller: 'homeController',
    })

    .when('/login', {
        templateUrl: 'app/views/login.html',
        controller: 'loginController',
    })

    .when('/user', {
        templateUrl: 'app/views/user.html',
        controller: 'userController',
    })

    .when('/domain', {
        templateUrl: 'app/views/domain.html',
        controller: 'domainController',
    })
    // caso não seja nenhum desses, redirecione para a rota '/'
    .otherwise({ redirectTo: '/' });
})
.factory('UserService', function () {
    return {
        token: 'empty'
    };
});