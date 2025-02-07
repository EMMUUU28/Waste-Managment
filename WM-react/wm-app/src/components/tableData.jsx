import React from "react";

function BinData(info){
    return(
        <tr>
                  <td class="px-4 py-3">{info.wet}</td>
                  <td class="px-4 py-3">{info.dry}</td>
                  <td class="px-4 py-3">{info.latitude}</td>
                  <td class="px-4 py-3 text-lg text-gray-900">{info.longitude}</td>
                </tr>
    )
}

export default BinData;