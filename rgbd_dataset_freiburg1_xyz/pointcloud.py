import open3d as o3d
color_raw = o3d.io.read_image("../../test_data/RGBD/color/00000.jpg")
depth_raw = o3d.io.read_image("../../test_data/RGBD/depth/00000.png")
rgbd_image = o3d.geometry.RGBDImage.create_from_color_and_depth(
    color_raw, depth_raw)
print(rgbd_image)