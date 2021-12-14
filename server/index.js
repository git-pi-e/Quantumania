// Imports
const express = require( 'express' );
const path = require( 'path' );

// Primitives
const PORT = 3000 || process.env.PORT;
const config = require( './config' );
const default_route = '../T33';

// Basics
const app = express();

// CONFIG
app.use( '/', express.static( path.join( __dirname, default_route ) ) );

config.endpoints.forEach( ( endpoint ) => {
    app.use( endpoint.url, express.static( path.join( __dirname, endpoint.folder ) ) );
} );

// ROUTES
app.get( '/', ( req, res ) => {
    res.send( `App running @ ${ PORT }` );
} );

app.listen( PORT, () => {
    console.log( `App listening @ ${ PORT }` );
} );