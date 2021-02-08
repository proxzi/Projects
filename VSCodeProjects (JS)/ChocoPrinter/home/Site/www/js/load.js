			// THE BROWSER LANGUAGE VARIABLE
			
			var userLanguage = window.navigator.userLanguage || window.navigator.language;
			var container, camera, scene, renderer, controls, light, vol, mesh, height, heightFinal, width, widthFinal, depth, depthFinal;

			var a = 0;

			if (userLanguage.substring(0,2)=="es")
				{
				
				}
				else
				{

				}
				    
			function init(file)
				{
				container = document.getElementById("container1");
				container.innerHTML= "";

				camera = new THREE.PerspectiveCamera(37.8,window.innerWidth/2/window.innerHeight,1,100000);

				camera.position.z=300;
				camera.position.y=-500;
				camera.position.x=-500;
				camera.up=new THREE.Vector3(0,0,1);

				scene = new THREE.Scene();
				scene.background = new THREE.Color(0x303030);
				

				var filename = file.name;
				var extension = filename.split(".").pop().toLowerCase();
				var reader = new FileReader();

				document.getElementById("container2").style.display="none";

				if (extension=="stl")
					{
					reader.readAsArrayBuffer(file);
					}
				else if (extension=="3ds")
					{
					reader.readAsArrayBuffer(file);
					}
				else if (extension=="obj")
					{
					reader.readAsText(file);
					}
					else
					{
					document.getElementById("container2").style.display="none";
					if (userLanguage.substring(0,2)=="es")
						{
						alert("ERROR: Por favor verifique que el modelo se encuentre en formato STL, OBJ o 3DS.");
						}
						else
						{
						alert("ERROR: Please check that the model is a STL, OBJ or 3DS model.");
						}
					}

				reader.addEventListener("load", function (event)
					{
					try
						{
						var contents = event.target.result;
						if (extension=="obj")
							{
							var object = new THREE.OBJLoader().parse(contents);
							var sceneConverter = new THREE.Scene();
							sceneConverter.add(object);
							var exporter = new THREE.STLExporter();
							contents = exporter.parse(sceneConverter);
							}
						else if (extension=="3ds")
							{
							var object = new THREE.TDSLoader().parse(contents);
							var sceneConverter = new THREE.Scene();
							sceneConverter.add(object);
							var exporter = new THREE.STLExporter();
							contents = exporter.parse(sceneConverter);
							}

						var geometry = new THREE.STLLoader().parse(contents);
						geometry.computeFaceNormals();
						geometry.computeVertexNormals();
						geometry.center();

						var material = new THREE.MeshPhongMaterial({color:0xffffff});
						mesh = new THREE.Mesh(geometry, material);

						// CALCULATING THE VOLUME
						vol = 0;

						mesh.traverse(function (child)
							{
							if (child instanceof THREE.Mesh)
								{
								var positions = child.geometry.getAttribute("position").array;
								for(var i=0;i<positions.length; i+=9)
									{
									var t1 = {};
									t1.x = positions[i+0];
									t1.y = positions[i+1];
									t1.z = positions[i+2];

									var t2 = {};
									t2.x = positions[i+3];
									t2.y = positions[i+4];
									t2.z = positions[i+5];

									var t3 = {};
									t3.x = positions[i+6];
									t3.y = positions[i+7];
									t3.z = positions[i+8];

									vol += signedVolumeOfTriangle(t1,t2,t3);
									}
								}
							});

						var box = new THREE.Box3().setFromObject(mesh);

						height = box.max.z - box.min.z;
						width = box.max.x - box.min.x;
						depth = box.max.y - box.min.y;

						var distance;

						if (height>width && height>depth)
							{
							distance = height * 2;
							}
						else if (width>height && width>depth)
							{
							distance = width * 2;
							}
						else if (depth>height && depth>width)
							{
							distance = depth * 2;
							}
						else
							{
							distance = depth * 4;
							}

						camera.position.set(0, -distance, 0);

						var x = distance + 200;
						var y = distance + 200;
						var division_x=Math.floor(x/10);
						var division_y=Math.floor(y/10);

						var wirePlane=new THREE.Mesh(new THREE.PlaneGeometry(x,y,division_x,division_y),new THREE.MeshPhongMaterial({emissive:0x707070,color:0x000000,wireframe:true,wireframeLinewidth:1}));
						wirePlane.receiveShadow=true;
						wirePlane.position.z = box.min.z - 0.1;
						scene.add(wirePlane);

						// AN ALTERNATIVE FOR MOVING THE OBJECT USING THE MOUSE WITHIN THE RENDERER
						// controls = new THREE.OrbitControls(camera, renderer.domElement);
						controls = new THREE.OrbitControls(camera, renderer.domElement);
						controls.update();

						scene.add(mesh);
						}
						catch(err)
						{
						document.getElementById("container2").style.display="none";
						if (userLanguage.substring(0,2)=="es")
							{
							alert("ERROR: Por favor verifique que el modelo se encuentre en formato STL, OBJ o 3DS.");
							}
							else
							{
							alert("ERROR: Please check that the model is a STL, OBJ or 3DS model.");
							}	
						}
					}, false);

				light = new THREE.HemisphereLight(0xE8E8E8,0x000000,1);
				light.position.set(0,0,0);
				scene.add(light);

				renderer = new THREE.WebGLRenderer({antialias:true});
				renderer.setSize(window.innerWidth/3,window.innerHeight/2);
				container.appendChild(renderer.domElement);

				requestAnimationFrame(animate);

				window.addEventListener("resize", onWindowResize, false );


				}

			function animate()
				{
				requestAnimationFrame(animate);
				light.position.copy(camera.getWorldPosition());
				renderer.render(scene,camera);
				}

			function onWindowResize()
				{
				camera.aspect = window.innerWidth/3 / window.innerHeight/2;
				camera.updateProjectionMatrix();
				renderer.setSize(window.innerWidth/3, window.innerHeight/2);
				}
			function runViewer()
				{
				var fileInput = document.getElementById("modelOBJ");
				if (fileInput.files[0]!=null)
					{
					init(fileInput.files[0]);
					fileInput.value = null;
					}
				}

			window.onload = function()
				{
					if(a == 0){
				container = document.getElementById("container1");
				container.innerHTML= "";

				camera = new THREE.PerspectiveCamera(37.8,window.innerWidth/2/window.innerHeight,1,100000);

				camera.position.z=300;
				camera.position.y=-500;
				camera.position.x=-500;
				camera.up=new THREE.Vector3(0,0,1);

				scene = new THREE.Scene();
				scene.background = new THREE.Color(0x303030);

				light = new THREE.HemisphereLight(0xE8E8E8,0x000000,1);
				light.position.set(0,0,0);
				scene.add(light);

				renderer = new THREE.WebGLRenderer({antialias:true});
				renderer.setSize(window.innerWidth/3,window.innerHeight/2);
				container.appendChild(renderer.domElement);

				requestAnimationFrame(animate);

				window.addEventListener("resize", onWindowResize, false );
				
					}
				document.getElementById("modelOBJ").disabled = false;
				document.getElementById("modelOBJ").value = null;

				}