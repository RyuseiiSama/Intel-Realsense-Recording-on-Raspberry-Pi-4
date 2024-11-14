#include <librealsense2/rs.hpp> // Include RealSense Cross Platform API
#include <iostream>
#include <cstdlib> // For std::atoi
#include <string>
#include <map>

// Function to parse command-line arguments
std::map<std::string, std::string> parse_args(int argc, char *argv[])
{
    std::map<std::string, std::string> args;
    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];
        size_t pos = arg.find('=');
        if (pos != std::string::npos)
        {
            std::string key = arg.substr(0, pos);
            std::string value = arg.substr(pos + 1);
            args[key] = value;
        }
    }
    return args;
}

int main(int argc, char *argv[])
{
    // Parse command-line arguments
    auto args = parse_args(argc, argv);

    // Check for required arguments
    if (args.find("--seconds") == args.end() || args.find("--output") == args.end())
    {
        std::cerr << "Usage: " << argv[0] << " --seconds=<number_of_seconds> --output=<absolute_path_to_save_recording>" << std::endl;
        return 1;
    }

    // Get the number of seconds to record from the command-line argument
    int num_seconds = std::atoi(args["--seconds"].c_str());
    if (num_seconds <= 0)
    {
        std::cerr << "Invalid number of seconds: " << num_seconds << std::endl;
        return 1;
    }

    // Get the output path from the command-line argument
    std::string output_path = args["--output"];
    if (output_path.empty() || output_path[0] != '/')
    {
        std::cerr << "Invalid output path: " << output_path << std::endl;
        return 1;
    }

    // Define the frames per second (FPS)
    const int fps = 30;

    // Calculate the maximum number of frames to record
    const int max_frames = num_seconds * fps;

    // Create a shared pointer to a pipeline
    auto pipe = std::make_shared<rs2::pipeline>();

    // Declare a new configuration
    rs2::config cfg;
    cfg.enable_stream(RS2_STREAM_COLOR, 640, 480, RS2_FORMAT_RGB8, fps);
    cfg.enable_stream(RS2_STREAM_DEPTH, 640, 480, RS2_FORMAT_Z16, fps);
    // cfg.enable_stream(RS2_STREAM_INFRARED, 640, 480, RS2_FORMAT_Y8, fps);
    cfg.enable_record_to_file(output_path); // Specify the output file

    // Start streaming with the configuration
    pipe->start(cfg);
    std::cout<< "Recording Started for " << num_seconds << " seconds" << std::endl;
    // Main loop
    int frame_count = 0;
    while (frame_count < max_frames)
    {
        // Wait for the next set of frames
        rs2::frameset frames = pipe->wait_for_frames();

        // Get the depth frame
        rs2::frame depth = frames.get_depth_frame();

        // Process the frames if needed (e.g., display, save, etc.)
        // ...

        // Increment the frame count
        frame_count++;
    }

    std::cout << "Recording saved to " << output_path << std::endl;

    return 0;
}