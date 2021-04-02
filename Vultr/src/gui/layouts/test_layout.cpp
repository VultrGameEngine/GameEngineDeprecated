#include <gui/layouts/test_layout.h>
#include <gui/layouts/test_state_widget.h>
#include <gui/framework/list_view.h>

using namespace Vultr::GUI;

Window *TestLayout()
{
    return new Window(new RootWidget({}));
}

Widget *RootWidget::Build(BuildContext *context)
{
    return new Center({
        .child = new Container({
            .child = new ListView({
                .builder =
                    [](BuildContext *context, int index) {
                        return new Container({
                            .child = new Container({
                                .color = glm::vec4(255, 0, 0, 255),
                            }),
                            // .child = new Row({
                            //     .children =
                            //         {
                            //             new Flex({
                            //                 .child = new Container({
                            //                     .color = glm::vec4(0, 255, 0,
                            //                     255),
                            //                     }),
                            //                 .flex = 2,
                            //             }),
                            //             new Flex({
                            //                 .child = new Container({
                            //                     .color = glm::vec4(0, 0, 255,
                            //                     255),
                            //                     }),
                            //                 .flex = 1,
                            //             }),
                            //         },
                            // }),
                            .height = 200,
			    .color = glm::vec4(0, 255, 0, 255),
                            // .borders = EdgeInsets::All(5),
                            // .border_color = glm::vec4(0, 0, 0, 255),
                        });
                    },
                .count = 5,

            }),
            .width = 1920,
            .height = 1080,
            .color = glm::vec4(0),
        }),
    });
    // return new Center({
    //     .child = new TestStateWidget({
    //         .text = "Join Game",
    //     }),
    // });
    // return new Center({
    //     .child = new Container({
    //         .child = new RichText({
    //             .text = "abcdygp,a!.;:",
    //             .font = "res/fonts/RobotoMono-Regular.ttf",
    //             .color = glm::vec4(0, 0, 0, 255),
    //         }),
    //         //         .child = new Row({
    //         //     .children =
    //         //         {
    //         //             new Flex({
    //         //                  .child = new Container({
    //         //                     .width = 250,
    //         //                     .height = 750,
    //         //                     .color = glm::vec4(255, 0, 0, 255),
    //         //                 }),
    //         //                 .flex = 1,
    //         //             }),
    //         //             new Container({
    //         //                 .width = 400,
    //         //                 .height = 400,
    //         //                 .color = glm::vec4(0, 255, 0,  255),
    //         //             }),
    //         //             new Flex({
    //         //             .child = new Container({
    //         //                 .width = 750,
    //         //                 .height = 250,
    //         //                 .color = glm::vec4(0, 0, 255, 255),
    //         //             }),
    //         //                 .flex = 5,
    //         //             }),
    //         //         },
    //         //     .alignment = Alignment::Center(),
    //         // }),
    //         // .width = 700,
    //         // .height = 500,
    //         .color = glm::vec4(255),
    //     }),
    // });
    // return ;
}
