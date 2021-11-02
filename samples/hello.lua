
render = require "fwalp_renderer"
color = require "fwalp_color"

function update(time)
    print ("updated: " ..  time)

    render:set_color(color.white)

    render:draw_rec(100, 100, 100, 100)
end

function draw()

end

