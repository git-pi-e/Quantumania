f = t => document.querySelector( t );
fA = t => [ ...document.querySelectorAll( t ) ];

get_file_loc = async n => fetch( './assets/includes/' + n ).then( r => r.text() );

( function () {
    // GET INSERTS THEN FOR EACH
    // GET HREF THEN FETCH HREF
    // INNER HREF
    fA( '[insert]' ).forEach( i => get_file_loc( i.getAttribute( 'insert' ) ).then( t => i.innerHTML = t ) )
} )();