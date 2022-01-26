const path = require( 'path' );

module.exports = {
    mode: 'production',
    entry: './js/wasm.js',
    output: {
        path: path.resolve( __dirname, 'bundle' ),
        filename: 'bundle.js',
    },
    experiments: {
        asyncWebAssembly: true,
        syncWebAssembly: true
    }
};