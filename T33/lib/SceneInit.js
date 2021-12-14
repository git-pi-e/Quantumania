import * as THREE from 'https://cdn.jsdelivr.net/npm/three@0.121.1/build/three.module.js';
import { OrbitControls } from 'https://cdn.jsdelivr.net/npm/three@0.121.1/examples/jsm/controls/OrbitControls.js';


export default class SceneInit {
  constructor ( canvasID, camera, scene, controls, renderer, fov = 36 ) {
    this.fov = fov;
    this.scene = scene;
    this.camera = camera;
    this.controls = controls;
    this.renderer = renderer;
    this.canvasID = canvasID;
  }

  initScene () {
    this.camera = new THREE.PerspectiveCamera(
      this.fov,
      window.innerWidth / window.innerHeight,
      1,
      1000
    );
    this.camera.position.z = 196;

    this.clock = new THREE.Clock();
    this.scene = new THREE.Scene();

    this.uniforms = {
      u_time: { type: "f", value: 1.0 },
      colorB: { type: "vec3", value: new THREE.Color( 0xfff000 ) },
      colorA: { type: "vec3", value: new THREE.Color( 0xffffff ) },
    };

    // specify a canvas which is already created in the HTML file and tagged by an id
    // aliasing enabled
    const canvas = document.getElementById( this.canvasID );
    this.renderer = new THREE.WebGLRenderer( {
      canvas,
      antialias: true,
    } );

    this.renderer.setSize( window.innerWidth, window.innerHeight );
    document.body.appendChild( this.renderer.domElement );

    this.controls = new OrbitControls( this.camera, this.renderer.domElement );

    // if window resizes
    window.addEventListener( "resize", () => this.onWindowResize(), false );
  }

  animate () {
    // NOTE: Window is implied.
    window?.requestAnimationFrame( this.animate.bind( this ) );
    this.render();
    this.controls.update();
  }

  render () {
    this.uniforms.u_time.value += this.clock.getDelta();
    this.renderer.render( this.scene, this.camera );
  }

  onWindowResize () {
    this.camera.aspect = window.innerWidth / window.innerHeight;
    this.camera.updateProjectionMatrix();
    this.renderer.setSize( window.innerWidth, window.innerHeight );
  }
}
