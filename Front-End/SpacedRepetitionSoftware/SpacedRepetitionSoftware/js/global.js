

$(function () {

    initializeJQueryEvents();

    $('.handle').on('click', function () {
        $('nav ul').toggleClass('showing');
    });


});


function initializeJQueryEvents() {

    
    $("#btnRegister").click(function () {
        $("#divUser").show(200);
    });

    $("#btnLogin").click(function () {
        $("#divLogin").show(200);
    });

    $("#btnNewDeck").click(function () {
        $("#divNewDeck").show(200);
    });

    $("#btnCancelarDeck").click(function () {
        $("#divNewDeck").hide(200);
    });

    $("#btnCancelarWord").click(function () {
        $("#divNewWord").hide(200);
    });

    $("#btnCancelarStudy").click(function () {
        $("#divStudy").hide(200);
    });

    $("#btnCancelarHistory").click(function () {
        $("#divHistory").hide(200);
    });

    $('.full-form .input-group input').focusout(function () {

        var text_val = $(this).val();

        if (text_val === "") {

            $(this).removeClass('has-value');

        } else {

            $(this).addClass('has-value');

        }
    });
}
