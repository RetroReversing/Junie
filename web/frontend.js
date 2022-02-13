let frontend_status = { paused: false, startAt: 0 };
        

function run(system, core, game) {
    //Start core execution
    MTY_Start(`/${core.library}.wasm`, {
        js_get_host:  (value, length) => MTY_StrToC(window.location.hostname, value, length),
        js_get_port:  ()              => window.location.port ?? 0,
        js_is_secure: ()              => location.protocol.indexOf('https') != -1,

        js_get_system: (value, length) => MTY_StrToC(system,    value, length),
        js_get_core:   (value, length) => MTY_StrToC(core.name, value, length),
        js_get_game:   (value, length) => MTY_StrToC(game,      value, length),

        js_read_file:  JUN_ReadFile,
        js_write_file: JUN_WriteFile,
        retro_deinit: ()=> console.log("retro_deinit"),
        get_frontend_status: ()=> {
            const json_string = JSON.stringify(frontend_status)+"\0";
            const MAX_COMMAND_LENGTH = 1024;
            MTY.libRRcommand = MTY_Alloc(MAX_COMMAND_LENGTH);
            if (json_string.length >MAX_COMMAND_LENGTH ) {
                console.error("Warning: please increase MAX_COMMAND_LENGTH to at least:", json_string.length);
            }
            const c_str = MTY_StrToC(json_string,MTY.libRRcommand, json_string.length);
            console.log("get_frontend_status", json_string, c_str);
            return c_str;
        }
    });
    

    //Prevent mobile keyboard
    MTY.clip.readOnly = true;
}

        //Retrieve context parameters
        const params = decodeURI(window.location.pathname).split('/');
        const system = params[1];

        if (system == 'play') {
            var input = document.createElement('input');
            input.type = 'file';
            document.body.appendChild(input);

            input.onchange = e => {
                const file = e.target.files[0];

                const game      = file.name;
                const extension = game.substring(game.lastIndexOf('.') + 1);
                const system    = extensions[extension];
                const core      = systems[system];

                document.body.removeChild(input);

                const _fetch = window.fetch;
                window.fetch = (input, init) => {

                    //Returning the local game file if the request matches
                    if (input.endsWith(`${system}/${game}`)) {
                        const response = new Response(file, { status: 200 });
                        return new Promise(resolve => resolve(response));
                    }

                    return _fetch(input, init);
                }

                run(system, core, game);
            }
        } else {
            const core = systems[system];
            const game = params[2];

            run(system, core, game)
        }

        function startlibRR(json_string = '{ "category": "play", "state": { "startAt": 0, "paused": false } }\0') {
            MTY.libRRcommand = MTY_Alloc(json_string.length);
            const c_str = MTY_StrToC(json_string,MTY.libRRcommand, json_string.length);
            const result = MTY.module.instance.exports.libRR_parse_message_from_emscripten(c_str);
            // console.log("Result:", result, MTY_StrToJS(result));
        }