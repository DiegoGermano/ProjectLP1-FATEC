

$(function () {

    initializeJQueryEvents();

    $('.handle').on('click', function () {
        $('nav ul').toggleClass('showing');
    });
});


function initializeJQueryEvents() {

    $('.full-form .input-group input').focusout(function () {

        var text_val = $(this).val();

        if (text_val === "") {

            $(this).removeClass('has-value');

        } else {

            $(this).addClass('has-value');

        }
    });
}
