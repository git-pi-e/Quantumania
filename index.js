"use strict"
import express from 'express';
import fetch from 'node-fetch';
import path from 'path';

const endpoints = [
    {
        "name": "T33",
        "url": "/T33",
        "folder": "../T33"
    }
];
const __dirname = path.resolve();

const PORT = 3000 || process.env.PORT;
const default_route = './';
const app = express();

app.use( '/', express.static( path.join( __dirname, default_route ) ) );
endpoints.forEach( ( endpoint ) => app.use( endpoint.url, express.static( path.join( __dirname, endpoint.folder ) ) ) );

app.get( '/', ( req, res ) => res.send( `App running @ ${ PORT }` ) );
app.get( '/qt', ( req, res ) => {
    fetch( `https://qrng.anu.edu.au/wp-content/plugins/colours-plugin/get_image_bw.php?_=${ Date.now() }` )
        .then( r => r.text() )
        .then( d => res.send(
            btoa(
                d.split( '64,' )[ 1 ]
            ).split( '' ).map( e => e.charCodeAt( 0 ) % 2 ).join( '' )
        ) );
} );

app.listen( PORT, () => console.log( `App listening @ ${ PORT }` ) );