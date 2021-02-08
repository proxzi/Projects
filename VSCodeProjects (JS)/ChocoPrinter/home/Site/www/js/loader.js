window.onload = function(){
    "use strict";
    
    var w = window.innerWidth/3, h = window.innerHeight/2;
    
    var renderer = new THREE.WebGLRenderer();
    renderer.setSize(w, h);
    var view = document.getElementById("view");
    view.appendChild(renderer.domElement);
    
    var camera = new THREE.PerspectiveCamera(90, w / h, 1, 1000);
    camera.position.set(0, -450, 450);
    var controls = new THREE.TrackballControls(camera, view);
    
    var scene = new THREE.Scene();
    scene.add(new THREE.AmbientLight(0x666666));
    
    var light1 = new THREE.DirectionalLight(0xffffff);
    light1.position.set(0, 100, 100);
    scene.add(light1);
    
    var light2 = new THREE.DirectionalLight(0xffffff);
    light2.position.set(0, -100, -100);
    scene.add(light2);
    
    var mat = new THREE.MeshPhongMaterial({
        color: 0x6699cc, ambient: 0x33ff00, specular: 0x030303,
    });
    var obj = new THREE.Mesh(new THREE.Geometry(), mat);
    scene.add(obj);
    
    var planeGeometry = new THREE.PlaneGeometry(600,600,1,1);
    var planeMaterial = new THREE.MeshLambertMaterial({color: 0xB4B8B0});
    var plane = new THREE.Mesh(planeGeometry,planeMaterial);
    scene.add(plane);

    var loop = function loop() {
        requestAnimationFrame(loop);
        //obj.rotation.z += 0.05;
        controls.update();
        renderer.clear();
        renderer.render(scene, camera);
    };
    loop();
    
    // file load
    var openFile = function (file) {
        var reader = new FileReader();
        reader.addEventListener("load", function (ev) {
            var buffer = ev.target.result;
            var geom = loadStl(buffer);
            scene.remove(obj);
            obj = new THREE.Mesh(geom, mat);
            scene.add(obj);
        }, false);
        reader.readAsArrayBuffer(file);
    };
    
    // file input button
    var input = document.getElementById("file");
    input.addEventListener("change", function (ev) {
        var file = ev.target.files[0];
        openFile(file);
    }, false);
    
    // dnd
    view.addEventListener("dragover", function (ev) {
        ev.stopPropagation();
        ev.preventDefault();
        ev.dataTransfer.dropEffect = "copy";
    }, false);
    view.addEventListener("drop", function (ev) {
        ev.stopPropagation();
        ev.preventDefault();
        var file = ev.dataTransfer.files[0];
        openFile(file);
    }, false);
}
