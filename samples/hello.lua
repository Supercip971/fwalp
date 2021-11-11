
render = require "fwalp_renderer"
color = require "fwalp_color"

final_res_color = color.red
function update(time)
    print ("updated: " ..  time)

    if time > 50 then
        final_res_color = color.white
    end
end

function draw()
 
    render:set_color(final_res_color)

    render:draw_rec(100, 100, 100, 100)
end

