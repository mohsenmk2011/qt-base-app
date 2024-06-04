import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

Item {
    id: circleImage
    property alias source: img.source
    property alias sourceDefault: imgDefault.source

    Rectangle {
        anchors.fill: parent
        radius: parent.width / 2
        color: "lightgrey"
    }

    Image {
        id: imgDefault
        anchors.centerIn: parent
        fillMode: Image.Pad
        width: 27
        height: 27
        visible: !img.visible
    }

    ShaderEffect {
        anchors.fill: parent
        visible: img.visible
        property var source: ShaderEffectSource {
            sourceItem: img
        }
        fragmentShader: "
            varying vec2 qt_TexCoord0;
            uniform sampler2D source;

            void main() {
                vec2 center = vec2(0.5, 0.5);
                float radius = 0.5;
                vec2 coord = qt_TexCoord0 - center;
                float dist = length(coord);

                if (dist < radius) {
                    gl_FragColor = texture(source, qt_TexCoord0);
                } else {
                    discard;
                }
            }
        "
    }

    Image {
        id: img
        anchors.fill: parent
        fillMode: Image.PreserveAspectCrop
        smooth: true
        visible: true // Ensure the image is visible by default for testing
    }
}
