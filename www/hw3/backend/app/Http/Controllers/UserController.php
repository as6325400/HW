<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use Illuminate\Support\Str;

class UserController extends Controller
{
    //
    public function userprofile(Request $request)
    {   
        $token = $request->header('Authorization');
        if (Str::startsWith($token, 'Bearer ')) {
            // 提取 token 部分（移除 "Bearer "）
            $token = Str::substr($token, 7);
        }
        $user = auth()->user();
        return response()->json($user, 200);
    }
}
