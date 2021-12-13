// Imports
const express = require( 'express' );
const path = require( 'path' );

// Primitives
const PORT = 3000 || process.env.PORT;
const default_route = '../T33';

// Basics
const app = express();

// CONFIG
app.use( '/', express.static( path.join( __dirname, default_route ) ) );

app.use( '/T33', express.static( path.join( __dirname, '../T33' ) ) );
app.use( '/Quandris', express.static( path.join( __dirname, '../Quandris' ) ) );

// ROUTES
app.get( '/', ( req, res ) => {
    res.send( `App running @ ${ PORT }` );
} );

app.listen( PORT, () => {
    console.log( `App listening @ ${ PORT }` );
} );