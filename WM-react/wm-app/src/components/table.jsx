import React from "react";
import data from "../data";
import BinData from "./tableData";

function tableData(data){
    return(
        <BinData
        wet = {Math.round((data.field1/15)) + "%"}
        dry = {Math.round((data.field2/15)) + "%"}
        latitude = "19.04"
        longitude = "72.81"
    />
    )
}



function Table(){
    return(
        <section class="text-gray-600 body-font">
        <div class="container px-5 py-24 mx-auto">
          <div class="flex flex-col text-center w-full mb-20">
            <h1 class="sm:text-4xl text-3xl font-medium title-font mb-2 text-gray-900">Bin Information</h1>
            <p class="lg:w-2/3 mx-auto leading-relaxed text-base">Turning trash into treasure, one byte at a time.</p>
          </div>
          <div class="lg:w-2/3 w-full mx-auto overflow-auto">
            <table class="table-auto w-full text-left whitespace-no-wrap">
              <thead>
                <tr>
                  <th class="px-4 py-3 title-font tracking-wider font-medium text-gray-900 text-sm bg-gray-100 rounded-tl rounded-bl">Wet Waste</th>
                  <th class="px-4 py-3 title-font tracking-wider font-medium text-gray-900 text-sm bg-gray-100">Dry Waste</th>
                  <th class="px-4 py-3 title-font tracking-wider font-medium text-gray-900 text-sm bg-gray-100">Latitute</th>
                  <th class="px-4 py-3 title-font tracking-wider font-medium text-gray-900 text-sm bg-gray-100">Longitude</th>
                </tr>
              </thead>
              <tbody>
                {data.map(tableData)}
              </tbody>
            </table>
          </div>
        </div>
      </section>
    )
}

export default Table;
