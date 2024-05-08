<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;

class UserController extends Controller
{
    //
    public function login(Request $request)
    {   
        $data = [
            'name' => 'John Doe',
            'age' => 25,
            'email' => 'sadasdad'
        ];
        return response()->json($data);
    }
}
