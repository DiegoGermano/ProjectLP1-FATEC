

$(function () {

    initializeJQueryEvents();

    $('.handle').on('click', function () {
        $('nav ul').toggleClass('showing');
    });


});


function initializeJQueryEvents() {

    $("#btnNewDeck").click(function () {
        $("#divNewDeck").show(50);
    });

    $("#btnCancelarDeck").click(function () {
        $("#divNewDeck").hide(50);
    });

    $("#btnCancelarWord").click(function () {
        $("#divNewWord").hide(50);
    });

    $("#btnCancelarStudy").click(function () {
        $("#divStudy").hide(50);
    });

    $("#btnCancelarHistory").click(function () {
        $("#divHistory").hide(50);
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
