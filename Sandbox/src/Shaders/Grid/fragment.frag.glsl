#version 460 core

layout(std140, binding = 0) uniform Viewport
{
    uint width;
    uint height;
};

layout(std140, binding = 2) uniform Camera
{
    mat4 view;
    mat4 projection;
    mat4 view_projection;
    mat4 inverse_view_projection;
};

layout(std140, binding = 5) uniform EnableGrid
{
    int enable_yz;
    int enable_xz;
    int enable_xy;
};

layout(location = 0) out vec4 color;

vec3 distance_from_gridlines(vec3 point, float gridline_interval) {
    vec3 remainder = mod(point, gridline_interval);
    return -abs(remainder - gridline_interval/2) + gridline_interval/2;
}

float gridline_alpha(float gridline_distance, float gridline_pixel_count)
{
    float pixel_width = fwidth(gridline_distance);

    return 1.0 - smoothstep(
        pixel_width,
        pixel_width * gridline_pixel_count,
        gridline_distance
    );
}

void main() {
    vec2 ndc = (gl_FragCoord.xy / vec2(width, height)) * 2.0 - 1.0;

    vec4 ray_near_h = inverse_view_projection * vec4(ndc, -1.0, 1.0);
    vec4 ray_far_h = inverse_view_projection * vec4(ndc, 1.0, 1.0);
    vec3 ray_near = ray_near_h.xyz / ray_near_h.w;
    vec3 ray_far = ray_far_h.xyz / ray_far_h.w;

    vec3 ray_direction = ray_far - ray_near;
    // t** is the scaling factor for the direction vector to reach the plane ** that crosses the origin
    float tyz = -ray_near.x / ray_direction.x;
    float txz = -ray_near.y / ray_direction.y;
    float txy = -ray_near.z / ray_direction.z;

    
    const float minor_gridline_interval = 1.0;
    const float minor_gridline_width = 2;
    float alpha = 0.0;
    float frag_depth = 1.0;

    if (0 < tyz && tyz < 1 && bool(enable_yz)) {
        vec3 intersect_yz = ray_near + tyz * ray_direction;
        vec3 distance_yz = distance_from_gridlines(intersect_yz, minor_gridline_interval);
        float alpha_yz = max(
            gridline_alpha(abs(distance_yz.y), minor_gridline_width),
            gridline_alpha(abs(distance_yz.z), minor_gridline_width)
        );
        
        if (alpha_yz > 0.0){
            vec4 clip_yz = view_projection * vec4(intersect_yz, 1.0);
            alpha = max(alpha, alpha_yz);
            frag_depth = min(frag_depth, clip_yz.z / clip_yz.w);
        }
    }
    if (0 <= txz && txz <= 1 && bool(enable_xz)) {
        vec3 intersect_xz = ray_near + txz * ray_direction;
        vec3 distance_xz = distance_from_gridlines(intersect_xz, minor_gridline_interval);
        float alpha_xz = max(
            gridline_alpha(abs(distance_xz.x), minor_gridline_width),
            gridline_alpha(abs(distance_xz.z), minor_gridline_width)
        );
        
        if (alpha_xz > 0.0){
            vec4 clip_xz = view_projection * vec4(intersect_xz, 1.0);    
            alpha = max(alpha, alpha_xz);
            frag_depth = min(frag_depth, clip_xz.z / clip_xz.w);
        }
    }
    if (0 <= txy && txy <= 1 && bool(enable_xy)) {
        vec3 intersect_xy = ray_near + txy * ray_direction;
        vec3 distance_xy = distance_from_gridlines(intersect_xy, minor_gridline_interval);
        float alpha_xy = max(
            gridline_alpha(abs(distance_xy.x), minor_gridline_width),
            gridline_alpha(abs(distance_xy.y), minor_gridline_width)
        );
        
        if (alpha_xy > 0.0){
            vec4 clip_xy = view_projection * vec4(intersect_xy, 1.0);    
            alpha = max(alpha, alpha_xy);
            frag_depth = min(frag_depth, clip_xy.z / clip_xy.w);
        }
    }

    if (alpha <= 0.0)
        discard;

    gl_FragDepth = frag_depth * 0.5 + 0.5 + 0.00001;

    color = vec4(0, 0, 0, alpha);
}