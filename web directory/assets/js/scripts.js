
jQuery(document).ready(function() {

    $('.page-container form').submit(function(){
        var username = $(this).find('.username').val();
        var password = $(this).find('.userpassword').val();
        if(username == '') {
            $(this).find('.error').fadeOut('fast', function(){
                $(this).css('top', '27px');
            });
            $(this).find('.error').fadeIn('fast', function(){
                $(this).parent().find('.username').focus();
            });
            return false;
        }
        if(password == '') {
            $(this).find('.error').fadeOut('fast', function(){
                $(this).css('top', '96px');
            });
            $(this).find('.error').fadeIn('fast', function(){
                $(this).parent().find('.userpassword').focus();
            });
            return false;
        }
    });

    $('.page-container form .username, .page-container form .userpassword').keyup(function(){
        $(this).parent().find('.error').fadeOut('fast');
    });

});
