"""Log a batch of oriented bounding boxes."""

import rerun as rr

rr.init("rerun_example_box3d_batch", spawn=True)

rr.log(
    "batch",
    rr.Boxes3D(
        centers=[[2, 0, 0], [-2, 0, 0], [0, 0, 2]],
        half_sizes=[[2.0, 2.0, 1.0], [1.0, 1.0, 0.5], [2.0, 0.5, 1.0]],
        radii=0.025,
        colors=[(255, 0, 0), (0, 255, 0), (0, 0, 255)],
        fill_mode="solid",
        labels=["red", "green", "blue"],
    ),
)
rr.log(
    "batch",
    rr.Transform3D(
        rotations=[
            rr.RotationAxisAngle.identity(),
            rr.RotationAxisAngle(axis=[0, 0, 1], angle=rr.Angle(deg=45)),
            rr.RotationAxisAngle(axis=[0, 1, 0], angle=rr.Angle(deg=30)),
        ],
    ),
)
