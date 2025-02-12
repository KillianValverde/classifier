/* classifier
 * Copyright (C) 2024 Killian Valverde.
 *
 * This file is part of classifier.
 *
 * classifier is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * classifier is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with classifier. If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @file        main/main.hpp
 * @brief       main entry point.
 * @author      Killian Valverde
 * @date        2024/10/15
 */

#define SPEED_MULTIPLATFORM_MAIN_WITH_UNICODE_SUPPORT
#include <speed/speed.hpp>

#include "../classifier/program.hpp"


int main(int argc, char* argv[])
{
    std::string messge;
    int retv;
    
    try 
    {
        classifier::program_args prog_args;
        spd::ap::arg_parser ap("classifier");
        
        ap.add_help_menu()
                .description("classifier parses a set of directories and builds a directory tree "
                             "in which links are placed in order to classify them into different "
                             "categories.")
                .epilogue("Example:\n"
                          "$ classifier ./Index ./Categories\n"
                          "\n"
                          "Example of JSON file:\n"
                          "{\n"
                          "    \"Published\": \"2013\",\n"
                          "    \"Genres\": [\"Drama\", \"Shoujo\"],\n"
                          "    \"Authors\": \"Keiko Suenobu\",\n"
                          "    \"Serialization\": \"Bessatsu Friend\",\n"
                          "    \"Mark\": 9,\n"
                          "    \"Languages\": [\"French\", \"English\"],\n"
                          "    \"Status\": \"Completed\"\n"
                          "}");

        ap.add_key_value_arg("--categories-file", "-f")
                .description("The categories file name. The default value is '.categories.json'.")
                .store_into(&prog_args.categories_file_nme);

        ap.add_keyless_arg("SOURCE-DIR")
                .description("Source directory.")
                .store_into(&prog_args.source_dir);

        ap.add_keyless_arg("DESTINATION-DIR")
                .description("Destination directory.")
                .store_into(&prog_args.destination_dir);
                
        ap.add_help_arg("--help", "-h")
                .description("Display this help and exit.");
                
        ap.add_version_arg("--version", "-v")
                .description("Output version information and exit.")
                .gplv3_version_information("0.0.0", "2024", "Killian Valverde");

        ap.parse_args(argc, argv);
        
        classifier::program prog(std::move(prog_args));
                
        return prog.execute();
    }
    catch (const classifier::exception_base& e)
    {
        messge = e.what();
        retv = 1;
    }
    catch (const std::exception& e)
    {
        messge = e.what();
        retv = -1;
    }
    catch (...)
    {
        messge = "Unknown error";
        retv = -1;
    }
    
    std::cerr << spd::ios::newl
              << spd::ios::set_light_red_text << "classifier: "
              << spd::ios::set_default_text << messge
              << std::endl;

    return retv;
}
